package project4.mystuff;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
/**
 *
 */
/**
 * @author stephensottosanti
 *
 */
public class ServiceRecordList{

  private static ServiceRecord recordList[];
  private static int size = 0;
  private static int spot = 0;


  /**.
   * Requests the service record list
   *
   * @param none
   *
   * @return
   *         returns the service record list for the week
   */
  public static void getServiceRecordList() throws IOException
  {
    FileWriter list = new FileWriter("ServiceRecordList.txt");
	String file_content; //what will be written to the file
	String temp0; //date and time submitted
	String temp1; //date of service
	int temp2; //provider number
	int temp3; //member number
	int temp4;//service code
	String temp5; //comments

	serviceRecord service;

	temp0 = "DT Submitted \t Date of Service \t Provider # \t Member # \t Service Code \t Comments \n";

	list.write(temp0);

    for(int i = spot; i < size; ++i) {
    	service = recordList[i];

    	temp0 = service.getDateAndTimeSubmitted();
    	temp1 = service.getServiceDate();
    	temp2 = service.getProviderNumber();
    	temp3 = service.getMemberNumber();
    	temp4 = service.getServiceCode();
    	temp5 = service.getComments();

    	file_content = temp0 + "\t" + temp1 + "\t" + temp2 + "\t" + temp3 + "\t" + temp4 + "\t" + temp5 + "\n";

    	list.write(file_content);
    }

    list.close();
  }

  /**.
   * adds a new service record
   *
   * @param none
   *
   * @return void
   *
   */
  public void addServiceRecord() {
    Scanner in = new Scanner(System.in);
    String dts = in.nextLine();
    System.out.println("Enter the date and time submitted in the form MM/DD/YYYY space 00:00 am/pm : ");

    String sd = in.nextLine();
    System.out.println("Enter the date the service was given in the form MM/DD/YYYY: ");

    int pn = in.nextInt();
    System.out.println("Enter the Provider number: ");

    int mn = in.nextInt();
    System.out.println("Enter the Member number: ");

    int sc = in.nextInt();
    System.out.println("Enter the service code that was used: ");

    String comment = "";

    String answer = in.nextLine();
    System.out.println("Would you like to enter a comment? type \"yes\" or \"no\": ");

    int var = answer.compareTo("yes");
    int var1 = answer.compareTo("no");

    if(var == 0) {
      comment = in.nextLine();
      System.out.println("Enter your comment (can only be 100 characters): ");

      if (comment.length() > 100)
      {
          comment = comment.substring(0, 100);
      }
    }
    else if(var1 == 0) {
    	comment = "no comment";
    }
    else { //they did not type yes or no
    	System.out.println("You did not type yes or no, no comment will added");
    	comment = "no comment";
    }


	recordList[size] = new serviceRecord(dts, sd, pn, mn, sc, comment);


	size += 1;
	in.close();
  }

  /**.
   * Sets new spot
   *
   * @param none
   *
   * @return none
   *
   */
  public void resetServiceRecordList() {
	  spot = size;
  }

  /**.
   * gets a specific service record based on date and time submitted
   *
   * @param none
   *
   * @return
   *        returns a specific service record based on name
   */
  public void getServiceRecord() {
	Scanner in = new Scanner(System.in);
	String x = in.nextLine();
    System.out.println("Enter the date and time the service record was submitted in the form MM/DD/YYYY(space)00:00am/pm : ");

	serviceRecord y = new serviceRecord();
	String temp;
	int var;

	for(int i = spot; i < size; ++i) {
		y = recordList[i];
		temp = y.getDateAndTimeSubmitted();
		var = temp.compareTo( x );

		if(var == 0) {
			System.out.println("Found the service record");
			String sd = y.getServiceDate();
	    	int pn = y.getProviderNumber();
	    	int mn = y.getMemberNumber();
	    	int sc = y.getServiceCode();
	    	String c = y.getComments();

	    	System.out.println("Service Date: " + sd);
	    	System.out.println("Provider Number: " + pn);
	    	System.out.println("Member Number: " + mn);
	    	System.out.println("Service Code: " + sc);
	    	System.out.println("Comments: " + c);

	    	in.close();
	    	return;
		}
	}

	in.close();
	System.out.println("Could not find specific service record \n");
  }
