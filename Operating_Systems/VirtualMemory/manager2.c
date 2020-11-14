/* Sottosanti.Stephen */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

/* constants */
#define PAGES 256       // Entries 
#define PAGE_SIZE 256   // Bytes
#define TLB_ENTRIES 16
#define FRAMES 128      // Entries
#define FRAME_SIZE 256  // Bytes
#define PHYSICAL_MEMORY FRAMES * FRAME_SIZE // 32,768 bytes
#define SECOND_MEMORY PAGES * PAGE_SIZE // 65,536 bytes
#define BUFFER 10

/* bitwise operators */
#define MASK 255
#define SHIFT 8

/* table sizes */
#define TLB_SIZE 16

struct tlb_entry
{
  unsigned char page_number;
  unsigned char frame_number;
  signed char valid;
};
typedef struct tlb_entry tlb_entry;

struct page_entry
{
  int frame_number;
  int clock;
  int valid;
};
typedef struct page_entry page_entry;

/* physical memory that will read in from the backing store when page fault occurs */
signed char physical_memory[PHYSICAL_MEMORY];
signed char *backing_ptr;

/* Page table and tlb table */
tlb_entry tlb_table[TLB_SIZE];
page_entry page_table[PAGES];

/* keep track of number of tlb entries */
int num_tlb_entries = 0;

/* return -1 if it is not in the tlb */
int search_tlb(unsigned char page)
{
  for(int i = 0; i < 16; i++) {
    tlb_entry *entry = &tlb_table[i];

    if(entry->page_number == page){
      return entry->frame_number;
    }
  }
  return -1;
}

/* Add to the TLB */
void add_tlb_entry(unsigned char page, unsigned char frame){
  tlb_entry *entry = &tlb_table[num_tlb_entries % TLB_SIZE];
  num_tlb_entries++;
  entry->page_number = page;
  entry->frame_number = frame;
}

/* return the page number for the least recently used page */
int LRU_page_finder(int current_clock){
  int lru_page = 0;
  int lru_clock = current_clock;

  for(int i = 0; i < PAGES; ++i){
    page_entry *entry = &page_table[i];
    int entry_clock = entry->clock;

    if(entry_clock != 0 && entry_clock < lru_clock){
      lru_clock = entry_clock;
      lru_page = i;
    }
  }

  return lru_page;
}

int main(int argc, const char *argv[]){

  /* counter used for lru */
  int current_clock = 0;

  if(argc != 2) {
    printf("Should be: ./a.out addresses.txt");
    exit(0);
  }

  const char *secondary_memory = "BACKING_STORE.bin";
  const char *input_file = argv[1];

  FILE *address_fp = fopen(input_file, "r");

  int backing_ptr_fd = open(secondary_memory, O_RDONLY);
  backing_ptr = mmap(0, SECOND_MEMORY, PROT_READ, MAP_PRIVATE, backing_ptr_fd, 0);

  /* fill all the pages with -1 */
  for(int i = 0; i < PAGES; i++) {
     page_table[i].clock = 0;
     page_table[i].valid = -1; 
  }

  /* Used to read lines of input file */
  char buf[BUFFER];

  int total_addresses = 0;
  int page_faults = 0;
  int tlb_hits = 0;

  /* the next unallocated physical page inside of the physical memory */
  int next_frame = 0;

  while(fgets(buf, BUFFER, address_fp) != NULL) {
  //for(int i = 0; i < 172; ++i){
    //fgets(buf, BUFFER, address_fp);
    total_addresses++;
    current_clock++;

    /* read in an address and change it to a 32-bit integer */
    int logical_address = atoi(buf);

    /* find the offset by using a mask of 255 which is 11111111 which will give you the rightmost 8 bits */
    int offset = logical_address & MASK;

    /* shift right 8 bits which gets rid of the offset and then use mask to get 8 rightmost bits which is now the page number */
    int page_number = (logical_address >> SHIFT) & MASK;
    
    int frame_number = search_tlb(page_number);
    
    /* TLB hits when frame_number does not equal -1 */
    if(frame_number != -1) {
      tlb_hits++;
    }
    else {
      /* check to see if it is in memory */
      int is_valid = page_table[page_number].valid;
      frame_number = page_table[page_number].frame_number;

      /* page fault, frame currently is not in main memory */
      if(is_valid == -1){
        /* Page Fault */
        page_faults++;
        frame_number = next_frame;
        next_frame++;

        /* Physical memory isn't full, no need to swap */
        if(frame_number < FRAMES){

          /* read in 256-byte page from the file BACKING_STORE and store it in an available page frame in physical memory */
          memcpy(physical_memory + frame_number * FRAME_SIZE, backing_ptr + page_number * FRAME_SIZE, FRAME_SIZE);

          page_table[page_number].frame_number = frame_number;
          page_table[page_number].valid = 1;
        }
        else{ 
          int replace_page = LRU_page_finder(current_clock);
          page_table[replace_page].valid = -1;
          page_table[replace_page].clock = 0;

          frame_number = page_table[replace_page].frame_number;

          /* read in 256-byte page from the file BACKING_STORE and store and replace a page frame in physical memory */
          memcpy(physical_memory + frame_number * FRAME_SIZE, backing_ptr + page_number * FRAME_SIZE, FRAME_SIZE);

          page_table[page_number].frame_number = frame_number;
          page_table[page_number].valid = 1;
        }

      }

      add_tlb_entry(page_number, frame_number);
    }
    
    page_table[page_number].clock = current_clock;

    int physical_address = (frame_number * FRAME_SIZE) + offset;
    signed char value = physical_memory[physical_address];
        
    printf("Logical address: %d  physicall address:  %d  Value:  %d\n", logical_address, physical_address, value);
  }

  printf("Number of Translated Addresses = %d\n", total_addresses);
  printf("Page faults = %d\n", page_faults);
  printf("Page Fault Rate = %.3f \n", page_faults / (1. * total_addresses));
  printf("TLB Hits = %d\n", tlb_hits);
  printf("TLB Hit Rate = %.3f\n", tlb_hits / (1. * total_addresses));

  return 0;
}