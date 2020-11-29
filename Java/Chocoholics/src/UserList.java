package spring2020team1;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import javax.swing.JOptionPane;

/**
 * UserList contains a complete list of all Members and Providers
 * Functionality to add, edit, or remove Members and Providers
 *
 * @author Parker Hopson
 */

public class UserList {

	private String MEMBERS_PATH = "memberlist.txt";
	private String PROVIDERS_PATH = "providerlist.txt";
	private List<Member> memberList;
	private List<Provider> providerList;

	/**
	 * Default constructor, uses default path to read members and providers from text file
	 * fills into two ArrayLists, one for members and one for providers
	 *
	 * @throws IOException when file cannot be read
	 */
	public UserList() {

		BufferedReader reader;
		memberList = new ArrayList<Member>();
		providerList = new ArrayList<Provider>();

		//Read existing userlist from text files

		try {
			reader = new BufferedReader(new FileReader(
					MEMBERS_PATH));
			String line = reader.readLine();
			while (line != null) {
				memberList.add(new Member(line));
				// read next line
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		try {
			reader = new BufferedReader(new FileReader(
					PROVIDERS_PATH));
			String line = reader.readLine();
			while (line != null) {
				providerList.add(new Provider(line));
				// read next line
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	/**
	 * Adds a Member, taken as parameter, into the member list
	 *
	 * @param inMem  Member object to add
	 */
	public void addMember(Member inMem) {
		memberList.add(inMem);
	}

	/**
	 * Adds a Provider, taken as parameter, into the member list
	 *
	 * @param inPro  Provider object to add
	 */
	public void addProvider(Provider inPro) {
		providerList.add(inPro);
	}


	/**
	 * Using id number to search, edits a member's data depending on integer passed in
	 *
	 * @param memNum  ID number of member to edit
	 *
	 * @param datType integer corresponding to attribute to edit
	 *
	 * @param dat  new data to replace in edited attribute
	 */
	public void editMember(int memNum, int datType, String dat) {
		Member temp;

		if(!doesMemberExist(memNum)) {
			JOptionPane.showMessageDialog(null, "Member does not exist in User List");
			return;
		}

		temp = searchMemberByNumber(memNum);

		switch(datType) {
		case 1:
			temp.setName(dat);
			break;
		case 2:
			temp.setAddress(dat);
			break;
		case 3:
			temp.setCity(dat);
			break;
		case 4:
			temp.setState(dat);
			break;
		case 5:
			temp.setZipCode(Integer.parseInt(dat));
			break;
		case 6:
			temp.setMembershipStatus(dat);
			break;
		default:
			break;
		}


	}

	/**
	 * Using id number to search, edits a provider's data depending on integer passed in
	 *
	 * @param memNum  ID number of member to edit
	 *
	 * @param datType integer corresponding to attribute to edit
	 *
	 * @param dat  new data to replace in edited attribute
	 */
	public void editProvider(int proNum, int datType, String dat) {
		if(!doesProviderExist(proNum)) {
			JOptionPane.showMessageDialog(null, "Provider does not exist in User List");
			return;
		}

		Provider temp = searchProviderByNumber(proNum);


		switch(datType) {
		case 1:
			temp.setName(dat);
			break;
		case 2:
			temp.setAddress(dat);
			break;
		case 3:
			temp.setCity(dat);
			break;
		case 4:
			temp.setState(dat);
			break;
		case 5:
			temp.setZipCode(Integer.parseInt(dat));
			break;
		default:
			break;
		}
	}

	/**
	 * does not remove member from list, sets member status to "Not Member"
	 *
	 * @param memNum  id number of member to delete
	 */
	public void deleteMember(int memNum) {
		if(!doesMemberExist(memNum)) {
			System.out.println("Member does not exist in User List");
		}else {
			Member temp = searchMemberByNumber(memNum);
			temp.setMembershipStatus("Not Member");
		}
	}

	/**
	 * removes provider from provider list entirely
	 *
	 * @param proNum  id number of provider to delete
	 */
	public void deleteProvider(int proNum) {
		if(!doesProviderExist(proNum)) {
			System.out.println("Provider does not exist in User List");
		}else {
			Provider temp = searchProviderByNumber(proNum);
			providerList.remove(temp);
		}
	}

	/**
	 * searching with id number, returns true if member is found in list and false otherwise
	 *
	 * @param memNum id number of member to delete
	 */
	public boolean doesMemberExist(int memNum) {
		for(int i = 0; i <= memberList.size(); i++) {
			if(memberList.get(i).getIdNumber() == memNum) {
				return true;
			}
		}
		return false;
	}

	/**
	 * searching with id number, returns true if provider is found in list and false otherwise
	 *
	 * @param proNum  id number of provider to delete
	 */
	public boolean doesProviderExist(int proNum) {
		for(int i = 0; i <= providerList.size(); i++) {
			if(providerList.get(i).getIdNumber() == proNum) {
				return true;
			}
		}
		return false;
	}

	/**
	 * searches with Name string and returns the member object that is found
	 *
	 * @param memName  name of member to search for
	 */
	public Member searchMemberByName(String memName) {
		for(int i = 0; i <= memberList.size(); i++) {
			if(memberList.get(i).getName().equals(memName)) {
				return memberList.get(i);
			}
		}
		throw new NoSuchElementException("Member not found in User List");
	}

	/**
	 * searches with Name string and returns the provider object that is found
	 *
	 * @param proName  name of provider to search for
	 */
	public Provider searchProviderByName(String proName) {
		for(int i = 0; i <= providerList.size(); i++) {
			if(providerList.get(i).getName().equals(proName)) {
				return providerList.get(i);
			}
		}
		throw new NoSuchElementException("Provider not found in User List");
	}


	/**
	 * searches with id number and returns the member object that is found
	 *
	 * @param memNum  id number of member to search for
	 */
	public Member searchMemberByNumber(int memNum) {
		for(int i = 0; i <= memberList.size(); i++) {
			if(memberList.get(i).getIdNumber() == memNum) {
				return memberList.get(i);
			}
		}
		throw new NoSuchElementException("Member not found in User List");
	}


	/**
	 * searches with id number and returns the provider object that is found
	 *
	 * @param proNum  id number of provider to search for
	 */
	public Provider searchProviderByNumber(int proNum) {
		for(int i = 0; i <= providerList.size(); i++) {
			if(providerList.get(i).getIdNumber() == proNum) {
				return providerList.get(i);
			}
		}
		throw new NoSuchElementException("Provider not found in User List");
	}


	/**
	 * function to write list of members and providers to a text file
	 *
	 */
	public void writeToFile() {
		File fmem = new File(MEMBERS_PATH);
		File fpro = new File(PROVIDERS_PATH);
		PrintStream f1, f2;

		fmem.delete();
		fpro.delete();

		try {
		    f1 = new PrintStream(new File(MEMBERS_PATH));
		    for(int i = 0; i < memberList.size(); i++) {
		    	f1.println(memberList.get(i).printAttributesToString());
		    }
		    f1.close();
		} catch (IOException e) {
		        // TODO Auto-generated catch block
		        e.printStackTrace();
		}

		try {
		    f2 = new PrintStream(new File(PROVIDERS_PATH));
		    for(int i = 0; i < providerList.size(); i++) {
		    	f1.println(providerList.get(i).printAttributesToString());
		    }
		    f2.close();
		} catch (IOException e) {
		        // TODO Auto-generated catch block
		        e.printStackTrace();
		}
	}
}
