package spring2020team1;

/**
 * User is an <i>abstract</i> class which is
 * the superclass of both Member and Provider.
 * User contains all necessary information for
 * the documentation and configuration of a user,
 * (with exception to member_status, which is set
 * by the Member subclass).
 * <p>
 * Member contains the following attributes to
 * describe a Member:
 * <ul>
 * <li> Name</li>
 * <li> ID Number</li>
 * <li> Street Address</li>
 * <li> City</li>
 * <li> State</li>
 * <li> ZIP Code</li>
 * </ul>
 * </p>
 * <p>
 * <b>NOTE: </b>The ID number of a User is <b>not</b>
 * explicitly defined or entered by anyone. Instead,
 * the ID Number is automatically assigned by using
 * a process which is functionally similar to
 * the MySQL function AUTO_INCREMENT, which automatically
 * assigns an ID number to each new User based on an
 * incremented counter variable.
 * </p>
 *
 *
 * @author 		Stephen Gregory
 * @version 	%I%, %G%
 * @since		1.0
 */
public abstract class User {

	/**
	 * counter variable used to auto_increment and
	 * create the id_number of a new User
	 */
	private static long count = 0;
	private static long maxCount = 999999999;

	private String name;
	private long idNumber;
	private String address;
	private String city;
	private String state;
	private int zipCode;
	private String serviceRecordListFilePath;
	private ServiceRecordList myServiceRecordList;


	/**
	 * Class constructor that creates EMPTY new User object.
	 * All class attributes of type String are initialized to "".
	 * All class attributes of type int are initialized to 0.
	 * <p>
	 * setServiceRecordList() is not called, because this function
	 * is essentially a placeholder, and therefore shouldn't have
	 * any serviceRecords to save.
	 * </p>
	 * <p>
	 * User is an <i>Abstract</i> class, which means that this
	 * constructor is only called by either a new Member
	 * instantiation, or a new Provider instantiation.
	 * </p>
	 */
	public User() {
		setName("");
		setIdNumber(0);
		setAddress("");
		setCity("");
		setState("");
		setZipCode(0)
	}


	/**
	 * Class constructor that creates new User object.
	 *  <p>
	 *  <b>NOTE: </b> id_number is automatically created and
	 *  assigned by a call to setIdNumber(++count). This
	 *  assures that no ID numbers are duplicated (each
	 *  id_number is unique).
	 *
	 * @param name				         The first and last name of the User
	 * 							         to be created, formatted as "first last".
	 * @param address			         The street address of the User to
	 * 							         be created.
	 * @param city				         The City of residence of the User
	 * 							         to be created.
	 * @param state				         The State of residence of the User
	 * 							         to be created.
	 * @param zipCode			         The ZIP code of residence. of the
	 * 							         User to be created.
	 * @param serviceRecordListFilePath      The file path where the serviceRecordList
	 *                                   is stored.
	 *
	 */
	public User(String name, String address, String city, String state, int zipCode, String serviceRecordListFilePath) {
		setName(name);
		setIdNumber(++count);
		setAddress(address);
		setCity(city);
		setState(state);
		setZipCode(zipCode);
		setServiceRecordFilePath(serviceRecordListFilePath);
		setServiceRecordList(serviceRecordListFilePath);
	}


	/**
	 * Class constructor that creates a new User object from a large, comma
	 * separated string. This constructor assumes that bigString is in a
	 * comma-delimited format.
	 * <p>
	 * This is the constructor that will be used automatically by the system,
	 * as the UserList is maintained in a large .txt file, with each User's
	 * attributes written on a separate line.
	 * </p>
	 *
	 * @param bigString            A String in comma-separated format containing
	 *                             all of the attributes corresponding to a User,
	 *                             in the following order/format:
	 *                             <ol>
	 *                             <li>name</li>
	 *                             <li>idNumber</li>
	 *                             <li>address</li>
	 *                             <li>city</li>
	 *                             <li>state</li>
	 *                             <li>zipCode</li>
	 *                             <li>serviceRecordListFilePath</li>
	 *                             </ol>
	 *
	 * @throws                     IllegalArgumentException if bigString
	 *                             doesn't contain all of the 7 parameters that it
	 *                             should.
	 * @throws                     IllegalArgumentException if bigString contains
	 *                             faulty parameters such as negative service codes,
	 *                             String where there should be ints, ints where
	 *                             there should be Strings, etc.
	 *
	 */
	public User(String bigString) {
	    final String DELIMITER = ",";
	    String[] tokens = bigString.split(DELIMITER);

	    if (tokens.length < 7) {
	        throw new IllegalArgumentException("Not enough parameters given in bigString.");
	    }

	    try {
	        String name = tokens[0];
	        long idNumber = Long.parseLong(tokens[1]);
	        String address = tokens[2];
	        String city = tokens[3];
	        String state = tokens[4];
	        int zipCode = Integer.parseInt(tokens[5]);
	        String serviceRecordListFilePath = tokens[6];

	        setName(name);
	        setIdNumber(idNumber);
	        setAddress(address);
	        setCity(city);
	        setState(state);
	        setZipCode(zipCode);
	        setServiceRecordFilePath(serviceRecordListFilePath);
	    }
	    catch (Exception e) {
	        throw new IllegalArgumentException(e + "\nThe parameters given in bigString were faulty.");
	    }
	}


	/**
	 * Creates a single comma-delimited string containing all of User's
	 * attributes.
	 * <p>
	 * The order of the attributes in the comma-separated string is
	 * as follows:
	 * <ol>
	 * <li>
	 *
     * @return                     A String in comma-separated format containing
     *                             all of the attributes corresponding to a User,
     *                             in the following order/format:
     *                             <ol>
     *                             <li>name</li>
     *                             <li>idNumber</li>
     *                             <li>address</li>
     *                             <li>city</li>
     *                             <li>state</li>
     *                             <li>zipCode</li>
     *                             <li>serviceRecordListFilePath</li>
     *                             </ol>
	 */
	public String printAttributesToString() {
	    String outputLine = this.name + "," + Long.toString(this.idNumber) + ","
	                        + this.address + "," + this.city + "," + this.state
	                        + "," + Integer.toString(this.zipCode) + ","
	                        + this.serviceRecordListFilePath;
	    return outputLine;
	}


	/**
	 * Returns the name of the User
	 *
	 * @return			The name of the User that is queried
	 */
	public String getName() {
		return this.name;
	}


	/**
	 * Assigns the first and last name of
	 * the user, formatted as: "first last"
	 *
	 * @param name		The new first and last name of the User,
	 * 					formatting in a single string as
	 * 					"first last"
	 */
	public void setName(String name) {
		this.name = name;
	}


	/**
	 * Returns the ID number of the User
	 *
	 * @return			The idNumber of the User that is queried
	 */
	public long getIdNumber() {
		return this.idNumber;
	}

	/**
	 * Maybe this should be deleted? Why should anyone be able
	 * to modify their own idNumber?
	 *
	 * @param idNumber	A 9-digit ID number which distinguishes
	 * 					unique numbers (auto-incremented)
	 *
	 * @exception		IllegalArgumentException if id_number is
	 * 					a negative number
	 * @exception		IllegalArgumentException if id_number is
	 * 					greater than the maximum allowed amount
	 * 					of 999999999
	 */
	public void setIdNumber(long idNumber) {
		if (idNumber < 0 || idNumber > maxCount) {
			throw new IllegalArgumentException("ID number must be a positive number. ");
		}
		else if (idNumber > maxCount) {
			throw new IllegalArgumentException("There are no ID numbers left "
					+ "(1 Billion Ids are already in use");
		}
		this.idNumber = idNumber;
	}


	/**
	 * Returns the street address of the User
	 *
	 * @return			The street address of the User that is queried
	 */
	public String getAddress() {
		return this.address;
	}


	/**
	 * Assigns the street address of the User
	 *
	 * @param address	A String representing a street address
	 */
	public void setAddress(String address) {
		this.address = address;
	}


	/**
	 * Returns the City of residence of the User
	 *
	 * @return			The City of residence of the User that is queried
	 */
	public String getCity() {
		return this.city;
	}


	/**
	 * Assigns the City of residence to a User
	 *
	 * @param city		A String representing a City
	 */
	public void setCity(String city) {
		this.city = city;
	}


	/**
	 * Returns the State of residence of the User
	 *
	 * @return			The State of residence of the User that is queried
	 */
	public String getState() {
		return this.state;
	}


	/**
	 * Assigns the State of residence to a User
	 *
	 * @param state		A String representing a State
	 */
	public void setState(String state) {
		this.state = state;
	}


	/**
	 * Returns the ZIP code of residence of the User
	 *
	 * @return			The ZIP code of residence of the User that is queried
	 */
	public int getZipCode() {
		return this.zipCode;
	}


	/**
	 * Assigns the ZIP Code of residence to a User
	 *
	 * @param state		A integer representing a ZIP code
	 *
	 * @exception		IllegalArgumentException if ZIP code is a negative
	 * 					number
	 */
	public void setZipCode(int zipCode) {
		if (zipCode < 0) {
			throw new IllegalArgumentException("ZIP code must be a positive number. ");
		}
		this.zipCode = zipCode;
	}


	/**
	 * Assigns the file path of the service record(s) corresponding to one User.
	 *
	 * @param serviceRecordListFilePath    The file path of the User's service record(s)
	 */
	public void setServiceRecordFilePath(String serviceRecordListFilePath) {
	    this.serviceRecordListFilePath = serviceRecordListFilePath;
	}


	/**
	 * Returns the file path of the User's service record(s).
	 *
	 * @return     The file path of the User's service record(s)
	 *             as a String
	 */
	public String getServiceRecordFilePath() {
	    return this.serviceRecordListFilePath;
	}


	/**
     * Assigns a serviceRecordList to the User.
     *
     * @param serviceRecordListFilePath    A list containing all of the services that
     *                             a member has been involved in
     */
    public void setServiceRecordList(String serviceRecordListFilePath) {
        this.myServiceRecordList = new ServiceRecordList(serviceRecordListFilePath);
    }


    /**
     * Returns the serviceRecordList of a User.
     * <p>
     * This serviceRecordList contains a list of all
     * of the services that a user has been involved in.
     * </p>
     * <p>
     * If the User is a Member, the serviceRecordList
     * will contain all of the services that the Member
     * has received.
     * </p>
     * <p>
     * If the User is a Provider, the serviceRecordList
     * will contain all of the services that the Provider
     * has given.
     * </p>
     *
     * @return     The file path of the User's service record(s)
     *             as a String
     */
    public serviceRecordList getServiceRecordList() {
        return this.myServiceRecordList;
    }
}
