package project4.mystuff;

/**
 *
 */
/**
 * @author stephensottosanti
 *
 */
public class ServiceRecord {

  private String dt_submitted; //date time submitted
  private String service_date;
  private int provider_number;
  private int member_number;
  private int service_code;
  private String comments; //can only be 100 characters


  /**
   * Default constructor
   */
  public serviceRecord() {
	  dt_submitted = "";
	  service_date = "";
	  provider_number = 0;
	  member_number = 0;
	  service_code = 0;
	  comments = "";
  }

  /**.
   * this is the first constructor
   */
  public serviceRecord(String dts, String sd, int pn, int mn, int sc, String comment) {
    dt_submitted = dts;
    service_date = sd;
    provider_number = pn;
    member_number = mn;
    service_code = sc;
    comments = comment;
  }

  /**.
   * asks for the date and time submitted
   *
   * @param none
   *
   * @return
   *        the date and time submitted
   */
  public String getDateAndTimeSubmitted(){
	return dt_submitted;
  }

  /**.
   * asks for the service date
   *
   * @param none
   *
   * @return sd
   *         the date of the service
   */
  public String getServiceDate(){
    return service_date;
  }

  /**.
   * asks for the provider number
   *
   * @param none
   *
   * @return pn
   *         the provider number
   */
  public int getProviderNumber() {
    return provider_number;
  }

  /**.
   * asks for the member number
   *
   * @param none
   *
   * @return mn
   *         the member number
   */
  public int getMemberNumber() {
    return member_number;
  }

  /**.
   * asks for the service code
   *
   * @param none
   *
   * @return sc
   *        the service code used
   */
  public int getServiceCode() {
    return service_code;
  }

  /**.
   * asks for service code
   *
   * @param none
   *
   * @return
   *        returns a comment if they wish to enter a comment
   */
  public String getComments() {
    return comments;
  }
}
