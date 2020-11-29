package spring2020team1;

/**
 *
 * Provider is a class which represents a ChocAn service provider.
 * A Provider object encapsulates all of the information that is
 * needed to distinguish and represent a provider in our database.
 * A provider is a subclass of the abstract class 'User', so it
 * inherits all attributes and methods from User.
 *
 * Provider does <b>not</b> contain any attributes or methods that
 * aren't already defined in User, so Provider simply calls both
 * the empty constructor of User, as well as the constructors of
 * User that take all necessary User info as parameters.
 *
 * @author		Stephen Gregory
 * @version		%I%, %G%
 * @since 		1.0
 */
public class Provider extends User {

	/**
	 * Class constructor that creates EMPTY new Provider object.
	 * All class attributes of type String are initialized to "".
	 * All class attributes of type int are initialized to 0.
	 * <p>
	 * This constructor calls the default constructor of its
	 * superclass, User, which is responsible for
	 * initializing every attribute as either 0 (for ints) or
	 * "" (for Strings)
	 */
	public Provider() {
		super();
	}

	/**
	 * Class constructor that creates new Provider object.
	 * <p>
	 * This constructor calls the constructor of its
	 * superclass, User, which is responsible for
	 * initializing every field.
	 *
	 * @param name				           The first and last name of the Member to be created,
	 * 							           formatted as "first last"
	 * @param address			           The street address of the Member to be created
	 * @param city				           The city of residence of the Member to be created
	 * @param state				           The state of residence of the Member to be created
	 * @param zipCode			           The ZIP code of residence of the Member to be
	 * 							           created
	 * @param serviceRecordListFilePath    The filepath containing the Provider's ServiceRecords
	 *
	 */
	public Provider(String name, String address, String city, String state, int zipCode, String serviceRecordListFilePath) {
		super(name, address, city, state, zipCode, serviceRecordFilePath);
	}


	/**
     * Class constructor that creates a new Provider object from a large, comma
     * separated string. This constructor assumes that bigString is in a
     * comma-delimited format.
     * <p>
     * This is the constructor that will be used automatically by the system,
     * as the ProviderList is maintained in a large .txt file, with each Provider's
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
    public Provider(String bigString) {
        super(bigString);
    }
}
