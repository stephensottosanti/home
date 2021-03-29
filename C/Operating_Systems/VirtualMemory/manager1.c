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
#define FRAMES 256      // Entries
#define FRAME_SIZE 256  // Bytes
#define PHYSICAL_MEMORY FRAMES * FRAME_SIZE // 65,536 bytes
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
};
typedef struct tlb_entry tlb_entry;

tlb_entry tlb_table[TLB_SIZE];

/* physical memory that will read in from the backing store when page fault occurs */
signed char physical_memory[PHYSICAL_MEMORY];
signed char *backing_ptr;

/* Page table */
int page_table[PAGES];

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

int main(int argc, const char *argv[]){

  if(argc != 2) {
    printf("Should be: ./a.out addresses.txt");
    exit(0);
  }

  const char *secondary_memory = "BACKING_STORE.bin";
  const char *input_file = argv[1];

  FILE *address_fp = fopen(input_file, "r");

  int backing_ptr_fd = open(secondary_memory, O_RDONLY);
  backing_ptr = mmap(0, PHYSICAL_MEMORY, PROT_READ, MAP_PRIVATE, backing_ptr_fd, 0);

  if(backing_ptr == MAP_FAILED){
    perror("Could not mmap\n");
    return 1;
  }

  /* fill all the pages with -1 */
  for(int i = 0; i < PAGES; i++) { page_table[i] = -1; }

  /* Used to read lines of input file */
  char buf[BUFFER];

  int total_addresses = 0;
  int page_faults = 0;
  int tlb_hits = 0;

  /* the next unallocated physical page inside of the physical memory */
  int free_frame = 0;

  while(fgets(buf, BUFFER, address_fp) != NULL) {
    total_addresses++;

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

      /* check to see if it is in page table */
      frame_number = page_table[page_number];

      if(frame_number == -1){
        /* Page Fault */
        page_faults++;

        frame_number = free_frame;
        free_frame++;

        /* read in 256-byte page from the file BACKING_STORE and store it in an available page frame in physical memory */
        memcpy(physical_memory + frame_number * PAGE_SIZE, backing_ptr + page_number * PAGE_SIZE, PAGE_SIZE);

        page_table[page_number] = frame_number;
      }

      add_tlb_entry(page_number, frame_number);
    }

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
