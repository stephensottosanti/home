ices that can be performed by a ChocAn
 * service provider.
 * It only contains an array of Service objects
 * called "serviceList" and the total number
 * of objects in that array, called "numServices"
 *
 * @author Stephen Gregory
 * @version     %I%, %G%
 * @since       1.0
 */
public class ProviderDirectory {

	Service[] serviceList;
	int numServices;


	/**
	 * Constructor for a ProviderDirectory object.
	 * <p>
	 * Takes a list of Service objects, and simply
	 * stores this list along with the length of the
	 * list into ProviderDirectory.
	 * </p>
	 *
	 * @param  serviceList     A list of Service objects, to be stored as
	 *                         an attribute called <i>serviceList</i>
	 */
	public ProviderDirectory(Service[] serviceList) {
		this.serviceList = serviceList;
		numServices = serviceList.length;
	}


	/**
	 * Find a Service in the Provider Directory using
	 * the Service's serviceCode.
	 *
	 * <p>Performs a simple linear search of serviceList.
	 * </p>
	 *
	 * @param  serviceCode     The 6-digit service code corresponding
	 *                         to the Service that we wish to find
	 *
	 * @throws                 NoSuchElementException if the specified
	 *                         serviceCode does not match any Services
	 *                         in the Provider Directory
	 */
	public Service findServiceByCode(int serviceCode) {
		for (int i = 0; i < this.numServices; i++) {
			if (this.serviceList[i].serviceCode == serviceCode) {
				return this.serviceList[i];
			}
		}
		// If serviceCode isn't found, throw a NoSuchElementException
		throw new NoSuchElementException("Service code \"" + serviceCode + "\" does not exist in Provider Directory.");
	}


	/**
	 * Insertion sort serviceList (sorted by Service name
	 * in ascending order alphabetically
	 */
	public void sortByName() {
		for (int i = 1; i < numServices; i++) {
			String key = this.serviceList[i].serviceName;
			int j = i - 1;
			while (j >= 0 && (this.serviceList[i].serviceName.compareTo(key) > 0)) {
				this.serviceList[j + 1].serviceName = this.serviceList[j].serviceName;
				j--;
			}
			this.serviceList[j + 1].serviceName = key;
		}
	}


	/**
	 * Insertion sort serviceList (sorted by Service code
	 * in ascending order
	 */
	public void sortByCode() {
		int n = this.serviceList.length;
		for (int i = 1; i < n; i++) {
			int key = this.serviceList[i].serviceCode;
			int j = i - 1;
			while (j >= 0 && this.serviceList[i].serviceCode > key) {
				this.serviceList[j + 1].serviceCode = this.serviceList[j].serviceCode;
				j--;
			}
			this.serviceList[j + 1].serviceCode = key;
		}
	}


	/**
	 * Query and retrieve the total number of available
	 * Services in the Provider Directory.
	 *
	 * @return             The total number of available, unique
	 *                     Services in the Provider Directory
	 */
	public int getNumServices() {
		return numServices;
	}
}
