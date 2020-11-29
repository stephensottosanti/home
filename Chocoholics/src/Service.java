package spring2020team1;

/**
 * Service represents one specific service that can
 * be performed by a ChocAn service provider.
 *
 *
 * @author Stephen Gregory
 * @version     %I%, %G%
 * @since       1.0
 */
public class Service {

		int serviceCode;
		String serviceName;
		String serviceDescription;
		float serviceFee;

		/**
		 * Parameterized constructor which creates a new service object
		 * that represents a service which can be performed by a ChocAn
		 * service provider.
		 *
		 * @param serviceCode             A 6-digit service code representing a unique
		 *                                identifier for a Service object.
		 * @param serviceName             The name of a Service, such as "30 minute counseling
		 *                                session", "1-week diet plan", etc.
		 * @param serviceDescription      A short description of the service.
		 * @param serviceFee              The fee (in dollars) of a Service.
		 */
		public Service(int serviceCode, String serviceName, String serviceDescription, float serviceFee) {
			setServiceCode(serviceCode);
			setServiceName(serviceName);
			setServiceDescription(serviceDescription);
			setServiceFee(serviceFee);
		}

		/**
		 * Query and retrieve the 6-digit service code
		 * of the Service
		 *
		 * @return                The 6-digit service code
		 */
		public int getServiceCode() {
			return this.serviceCode;
		}

		/**
		 * Assign a service code to the Service.
		 *
		 * @param serviceCode     The 6-digit service code
		 */
		public void setServiceCode(int serviceCode) {
			if (serviceCode < 0) {
				throw new IllegalArgumentException("Service Code must be a positive number. ");
			}
			this.serviceCode = serviceCode;
		}

		/**
		 * Query and retrieve the service name of
		 * the Service
		 * @return                The service name
		 */
		public String getServiceName() {
			return this.serviceName;
		}

		/**
		 * Assign a new name to a Service
		 *
		 * @param serviceName     The service name
		 */
		public void setServiceName(String serviceName) {
			this.serviceName = serviceName;
		}

		/**
		 * Query and retrieve the description of the service.
		 *
		 * @return                The description of the service
		 */
		public String getServiceDescription() {
			return this.serviceDescription;
		}

		/**
		 * Set the description of the Service.
		 *
		 * @param serviceDescription  A String representing the description of
		 *                            the Service
		 */
		public void setServiceDescription(String serviceDescription) {
			this.serviceDescription = serviceDescription;
		}

		/**
		 * Query and retrieve the fee (dollar amount) of
		 * the Service.
		 *
		 * @return                The amount in dollars corresponding to
		 *                        the Service
		 */
		public float getServiceFee() {
			return this.serviceFee;
		}


		/**
		 * Set the fee (dollar amount) of the Service.
		 *
		 * @param serviceFee      A float representing the dollar amount
		 *                        corresponding to the Service
		 */
		public void setServiceFee(float serviceFee) {
			if (serviceFee < 0.0) {
				throw new IllegalArgumentException("Service Fee must be a positive number. ");
			}
			this.serviceFee = serviceFee;
		}


}
