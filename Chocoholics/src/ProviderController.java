package spring2020team1;

/**
 * Provider controller is a control class which is responsible
 * accessing the provider directory and validating the provider
 *
 *
 * <p>
 * ProviderController can be invoked by an operator or
 * manager at any time
 * </p>
 *
 * @author      Stephen Sottosanti
 * @author      Parker Hopson
 * @version     %I%, %G%
 * @since       1.0
 */
public class ProviderController {
  private Provider currentProvider;
  private Member currentMember;
  private UserList myUserList;

  private UserList userList;


  public ProviderController() {
      userList = new UserList();
      currentMember = new Member();
      currentProvider = new Provider();
  }

  /**.
  * scans member card and adds member number
  *
  * @param int
  *        integer for the member number
  * @return
  *        the date and time submitted
  */
  public void scanMember(int member_num){
    //fill in here
  }

  /**.
  * will add a serivce to the servie list
  *
  * @param int
  *        the int is the service code
  * @return
  *        the date and time submitted
  */
  public void billMember(int service_code){
    ServiceRecordList.addServiceRecord();
  }

  /**.
  * access the provider directory
  *
  * @param none
  *
  * @return
  *        the date and time submitted
  */
  public void AccessProviderDirectory() {
    Service[] serviceList;
    int numServices;

    this.serviceList = serviceList;
    numServices = serviceList.length;

    for (int i = 0; i < this.numServices; i++) {
      if (this.serviceList[i].serviceCode == serviceCode) {
        return this.serviceList[i];
      }
    }
  }

  /**.
  * asks for the date and time submitted
  *
  * @param none
  *
  * @return
  *        the date and time submitted
  */
  public void validateProvider(int provider_num) {
    for(i = 0; i < userList.providerList.size(); ++i){
      if (userList.providerList.at(i).idNumber == provider_num){
        System.out.println("Provider has been validated");
        return;
      }
    }

    System.out.println("Provider was not found with given idNumber");
  }

  /**.
    * will check to see if member is a current member and will return
    * the status of the member
    *
    * @param int
    *        the members id number
    * @return string
    *        the status of the member if the member exists
    */
  public void validateMember(int member_num) {
    for(i = 0; i < userList.memberList.size(); ++i){
      if (userList.memberList.at(i).idNumber == member_num){
        System.out.println("Member has been found \n" + "Member status: " + userList.memberList.at(i).getMembershipStatus());
        return;
      }
    }

    System.out.println("Member was not found with given idNumber");
  }

  /**.
    * after a service is given the service code needs to be validated
    *
    * @param int
    *        the code for the service to be looked up
    * @return
    *        the description of the service so the provider can validate it
    *        is the correct service that was provided
    */
  public void validateServiceCode(int service_code){
    
    for (int i = 0; i < ProviderDirectory.numServices; i++) {
      if (ProviderDirectory.serviceList[i].serviceCode == service_code) {
        return 0;
      }
    }

    return 1;
  }

  /**.
    * a fuinction that prompts the provider for its provider number
    *
    * @param none
    *
    * @return int
    *        provider number
    */
  public int promptForProviderNumber(){
    Scanner in = new Scanner(System.in);

    int pn = in.nextInt();
    System.out.println("Enter a Provider number: ");

    in.close();

    return pn;
  }



}
