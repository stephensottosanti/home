package project4.src;

import java.io.FileWriter;
import java.util.Scanner;

/**
 * ReportController is a control class which is responsible
 * for the compilation and distribution of Service Record
 * Reports.
 *
 * <p>
 * ReportController can be invoked by an operator or
 * manager at any time, but it also includes functionality
 * to automatically compile and send reports every week.
 * </p>
 *
 * @author      stephen sottosanti
 * @author      parker hopson
 * @version     %I%, %G%
 * @since       1.0
 */
public class ReportController {

    private UserList myUserList;

    /**.
     * Constructor
     *
     * @param none
     *
     * @return none. Constructor
     *
     */
    public reportController() {
        x = new UserList(/*Path to UserList*/);
    }

    /**.
     * compiles and creates report for all members and providers
     *
     * @param none
     *
     * @return void
     *
     */
    public void runAllReports(){
      File all_reports = new FileWriter(/*need a path*/);

      File file = new File(x.MEMBERS_PATH);
      Scanner in = new Scanner(file);

      while(in.hasNextLine()) {
        String member_name = in.nextLine();

        //then copy members reports to a text file
      }

      in.close();

      File file = new File(x.PROVIDERS_PATH);
      Scanner in = new Scanner(file);

      while(in.hasNextLine()) {
        String provider_name = in.nextLine();

        //then copy all provider reports to a text file
      }

      in.close();

    }

    /**.
     * compiles and creates report for provider
     *
     * @param none
     *
     * @return void
     *
     */
    public void makeProviderReport(int provider_number) {
    FileWriter report = new FileWriter("providerReport.txt");
    String file_content = ""; //what will be written to the file
    Scanner in = new Scanner(System.in);
    int num = in.nextInt();

      serviceRecordList service;
      Provider temp =  myUserList.searchProviderByNumber(provider_number)
      service = temp.getServiceRecordList();

      if(num == 1) {
          int spot = service.getSpot();
          int size = service.getSize();
          file_content +=

          String header;
          for(int i = spot; i < size; ++i) {
          service = recordList[i];

          String date_time_submitted = service.getDateAndTimeSubmitted();
          String service_date = service.getServiceDate();
          int member_number = service.getMemberNumber();
          int service_code = service.getServiceCode();
          String comments = service.getComments();

          file_content = date_time_submitted + "\n" + service_date + "\n" + provider_number + "\n" + member_number + "\n" + service_code + "\n" + comments + "\n";

          report.write(file_content);
          }
      }



        list.close();
        in.close();
    }

    /**.
     * compiles and creates report for member
     *
     * @param none
     *
     * @return void
     *
     */
    public void makeMemberReport() {
    FileWriter list = new FileWriter("MemberReport.txt");
    }

    /**.
     * compiles and creates summary report for manager
     *
     * @param none
     *
     * @return void
     *
     */
    public void makeSummaryReportForManager() {
    //fill in here
    }

    /**.
     * compiles and creates summary report for manager
     *
     * @param none
     *
     * @return void
     *
     */
    public void makeEFTDataReport(){
      //fill in here
    }
