ackage spring2020team1;

/**
 * Member is a class which represents a ChocAn member.
 * A Member object encapsulates all of the information that is
 * needed to distinguish and represent a member in our database.
 * A member is a subclass of the abstract class 'User', so it
 * inherits all attributes and methods from User, except for
 * <b>one</b> attribute: membership_status.
 * A Member's membership_status may either be:
 * <ol>
 * 	<li>Member</li>
 * 	<li>Suspended Member</li>
 * 	<li>Not Member</li>
 * </ol>
 * <p>
 * 	<b>Note:</b> Members who have unsubscribed from ChocoAn
 * 	<b>may</b> remain in the database and marked as
 * 	"Not Member" <b>or</b> may be removed entirely.
 * </p>
 *
 *
 * @author		Stephen Gregory
 * @version		%I%, %G%
 * @since 		1.0
 */
public class Member extends User {

		String membershipStatus;


		/**
		 * Class constructor that creates EMPTY new Member object.
		 * All class attributes of type String are initialized to "".
		 * All class attributes of type int are initialized to 0.
		 * <p>
		 * This constructor calls the default constructor of its
		 * superclass, User, which is responsible for
		 * initializing everything as 0 or "" except for
		 * membership_status, which is set to 0 by
		 * Member()
		 * </p>
		 */
		public Member() {
			super();
			setMembershipStatus("");
		}


		/**
		 * Class constructor that creates new Member object.
		 * <p>
		 * This constructor calls the default constructor of
		 * its superclass, User, which is responsible for
		 * initializing every field except for
		 * membership_status, which is set by the call to
		 * setMembershipStatus()
		 *
		 * @param name				The first and last name of the Member to be
		 * 							created, formatted as "first last"
		 * @param address			The street address of the Member to
		 * 							be created
		 * @param city				The City of residence of the Member
		 * 							to be created
		 * @param state				The State of residence of the Member
		 * 							to be created
		 * @param zipCode			The ZIP code of residence of the
		 * 							Member to be created
		 * @param membershipStatus  The membership status of the Member. This
		 *                          String is STRICTLY one of the following:
		 *                          <ol>
		 *                          <li>Member</li>
		 *                          <li>Suspended Member</li>
		 *                          <li>Not Member</li>
		 *                          </ol>
		 * @param serviceRecordListFilePath   The filepath containing the
		 *                          Member's ServiceRecords
		 *
		 */
		public Member(String name, String address, String city, String state, int zipCode, String membershipStatus, String serviceRecordListFilePath) {
			super(name, address, city, state, zipCode, serviceRecordListFilePath);
			setMembershipStatus(membershipStatus);
		}


		/**
	     * Class constructor that creates a new Member object from a large, comma
	     * separated string. This constructor assumes that bigString is in a
	     * comma-delimited format.
	     * <p>
	     * <strong>This overrides the bigString constructor in Member's
	     * superclass, User.</strong>
	     * </p>
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
	     *                             <li>membershipStatus</li>
	     *                             <li>serviceRecordListFilePath</li>
	     *
	     * @throws                     IllegalArgumentException if bigString
	     *                             doesn't contain all of the 8 parameters that it
	     *                             should.
	     *
	     * @throws                     IllegalArgumentException if bigString contains
	     *                             faulty parameters such as negative service codes,
	     *                             String where there should be ints, ints where
	     *                             there should be Strings, etc.
	     *
	     */
	    public Member(String bigString) {
	        final String DELIMITER = ",";
	        String[] tokens = bigString.split(DELIMITER);

	        if (tokens.length < 8) {
	            throw new IllegalArgumentException("Not enough parameters given in bigString.");
	        }

	        try {
	            String name = tokens[0];
	            long idNumber = Long.parseLong(tokens[1]);
	            String address = tokens[2];
	            String city = tokens[3];
	            String state = tokens[4];
	            int zipCode = Integer.parseInt(tokens[5]);
	            String membershipStatus = tokens[6];
	            String serviceRecordListFilePath = tokens[7];

	            setName(name);
	            setIdNumber(idNumber);
	            setAddress(address);
	            setCity(city);
	            setState(state);
	            setZipCode(zipCode);
	            setMembershipStatus(membershipStatus);
	            setServiceRecordFilePath(serviceRecordListFilePath);
	        }
	        catch (Exception e) {
	            throw new IllegalArgumentException(e + "\nThe parameters given in bigString were faulty.");
	        }
	    }


	    /**
	     * Creates a single comma-delimited string containing all of Member's
	     * attributes.
	     *
	     * <p>
         * <strong>This overrides User.printAttributesToString() in Member's
         * superclass, User.</strong>
         * </p>
	     *
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
	                            + this.membershipStatus + "," + this.serviceRecordListFilePath;
	        return outputLine;
	    }


		/**
		 * Queries the Membership Status of a Member
		 * A Member's membership_status may either be:
		 * <ol>
		 * 	<li>Member</li>
		 * 	<li>Suspended Member</li>
		 * 	<li>Not Member</li>
		 * </ol>
		 *
		 * @return		The membership status of the Member
		 */
		public String getMembershipStatus() {
			return this.membershipStatus;
		}


		/**
		 * Assigns the membership status of a Member
		 * A Member's membership_status may either be:
		 * <ol>
		 * 	<li>Member</li>
		 * 	<li>Suspended Member</li>
		 * 	<li>Not Member</li>
		 * </ol>
		 *
		 * @param membership_status		String representing the membership
		 * 								status of a Member, whether they be
		 * 								a <b>Member</b>, <b>Suspended Member</b>,
		 * 								or <b>Not Member</b>
		 *
		 * @exception					IllegalArgumentException if membership_status
		 * 								is not <b>exactly</b> one of the following
		 * 								strings: <ol>
		 * 											<li>Member</li>
		 * 											<li>Suspended Member</li>
		 * 											<li>Not Member</li>
		 *                                       </ol>
		 */
		public void setMembershipStatus(String membershipStatus) {
			if (membershipStatus == "Member" || membershipStatus == "Suspended Member" || membershipStatus == "Not Member") {
				this.membershipStatus = membershipStatus;
			}
			else {
				throw new IllegalArgumentException("Membership Status can be either:\n  "
						+ "1. Member\n  2. Suspended Member\n  "
						+ "3. Not Member\n");
			}
		}
}
