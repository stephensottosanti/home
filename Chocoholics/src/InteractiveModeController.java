package spring2020team1;

import javax.swing.JOptionPane;

/**
 * Interactive Mode Controller is used by operators to manage and modify
 * the User List. The Controller is able to add, delete, or modify members and providers
 *  from the User List
 *
 * @author Parker Hopson
 *
 */

public class InteractiveModeController {

  UserList users;

  /**
  * Default Constructor
  * Creates user list from saved user list data by declaring new userlist object with default path
  * default path is saved in UserList
  *
  */
  public InteractiveModeController() {
	  users = new UserList();
  }


  /**
   * Collect and send info for new Provider into user list
   */
  public void addProvider(String name, String address, String city, String state, int zip_code) {
	  Provider newP = new Provider(name, address, city, state, zip_code);
	  users.addProvider(newP);
  }

  /**
   * Modifies a providers info in the user list
   * parameter datType relates to piece of data in Member object, converts to int
   * 1- Name 2- address 3- city 4- state 5- zip code
   */
  public void editProvider(int proNum, String datType, String dat) {
	  int dT;
	  switch(datType) {
	  case "Name": dT = 1;
		  break;
	  case "Address": dT = 2;
	  	  break;
	  case "City": dT = 3;
	  	  break;
	  case "State": dT = 4;
	  	  break;
	  case "Zip Code": dT = 5;
	  	  break;
	  default: dT = -1;
	  	  break;
	  }
	  users.editProvider(proNum, dT, dat);
  }

  /**
   * Removes a provider from the user list
   */
  public void removeProvider(int proNum) {
	  users.deleteProvider(proNum);
  }

  /**
   * collect and sends info for new Member into user list
   */
  public void addMember(String name, String address, String city, String state, int zip_code, String membership_status) {
	  Member newM = new Member(name, address, city, state, zip_code, membership_status);
	  users.addMember(newM);
  }

  /**
   * Modifies a members info in the user list
   * parameter datType relates to piece of data in Member object
   * 1- Name 2- address 3- city 4- state 5- zip code 6-member status
   */
  public void editMember(int memNum, String datType, String dat) {
	  int dT;
	  switch(datType) {
	  case "Name": dT = 1;
		  break;
	  case "Address": dT = 2;
	  	  break;
	  case "City": dT = 3;
	  	  break;
	  case "State": dT = 4;
	  	  break;
	  case "Zip Code": dT = 5;
	  	  break;
	  case "Member Status": dT = 6;
	  	  break;
	  default: dT = -1;
	  	  break;
	  }

	  users.editMember(memNum, dT, dat);
  }

  /**
   * "Removes" a member by setting the member status to inactive
   */
  public void removeMember(int memNum) {
	  users.deleteMember(memNum);
  }

  public void saveLists() {
	  users.writeToFile();
  }

}
