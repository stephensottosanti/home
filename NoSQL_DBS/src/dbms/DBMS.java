package dbms;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map.Entry;

import java.util.Set;

import database.Database;

/**
 * 
 * This class encapsulates a NoSQL Database as an object. It stores the 
 * fieldname and value using the Document class 
 * 
 * @author Stephen Sottosanti 
 *
 */
public class DBMS {
	private enum OCP{
		Operation,
		Condition,
		Projection,
		NONE
	}
	
	private enum Operation{
		FIND,
		SORT,
		NEITHER
	}
	
	/**
	 * Linked Hash Map to store all of the documents 
	 */
	private ArrayList<LinkedHashMap<String, Integer>> database;
	
	/**
	 * Linked Hash Map to store all of the queries
	 */
	private ArrayList<LinkedHashMap<String, Integer>> query;
	
	public DBMS() {
		database = new ArrayList<LinkedHashMap<String, Integer>>();
		query = new ArrayList<LinkedHashMap<String, Integer>>();
	}

	/**
	 * This is the main method
	 * @param agrs
	 * @throws FileNotFoundException
	 */
	public static void main(String agrs[]) throws FileNotFoundException
	{
		DBMS dbms = new DBMS();
		
		// The names of the files that will be used to create and query the database 
		String docsFile = "data.txt";
		String queryFile = "final.txt";
		
		dbms.database = Database.createDatabase(docsFile, dbms.database);
		dbms.runQueries(queryFile);
		
	}
	
	public void runQueries(String queryFile) 
	{
		try {
			// Create an instance of a buffer reader to use to read in documents from a file
			BufferedReader lineReader = new BufferedReader(new FileReader(queryFile));
		    String currentLine = null;
		    
		    int numQuery = 0;
		    OCP currentStep = null;
		    Operation FS = Operation.NEITHER;
		    String projection = null;
		    ArrayList<String> conditions = new ArrayList<String>();
		    
		    System.out.println("--------------------------");
		    while ((currentLine = lineReader.readLine()) != null) {
		    	// Print out the query
		    	if(currentLine.equals("")) {
		    		; // Ignore blank lines
		    	} 
		    	else {
		    		System.out.print(currentLine);
		    		
		    		// Determine which part of the query you are currently on 
			    	if(currentLine.equals("FIND") || currentLine.equals("SORT")) currentStep = OCP.Operation;
			    	
			    	else if(currentLine.contains(";")) currentStep = OCP.Projection;
			    	
					else if(currentLine.contains("=") || currentLine.contains(">") || currentLine.contains("<") || currentLine.equals("Y")) 
						currentStep = OCP.Condition;
					
					else {
						currentStep = OCP.NONE;
						System.out.print("     !! invalid !!");
					}
			    	
			    	System.out.println();
		    	
		    	
			    	// Prepare the query
			    	if(currentStep == OCP.Operation) {
			    		if(currentLine.equals("FIND")) FS = Operation.FIND;
			    		else if(currentLine.equals("SORT")) FS = Operation.SORT;
					}
					else if(currentStep == OCP.Condition) {
						conditions.add(currentLine);
					}
					else if(currentStep == OCP.Projection) {
						if(FS == Operation.NEITHER) {
							numQuery++;
							System.out.println("\nQuery #" + numQuery + ":");
							System.out.println("Error! Your query must start with either FIND or SORT");
							System.out.println("--------------------------");
							conditions.clear();
						}
						else {
							numQuery++;
							System.out.println("\nQuery #" + numQuery + ":");
							projection = currentLine.replace(";", "");
							projection = projection.trim();
							
							// projection is the last line so execute query and then reset everything for the next query
							if(FS == Operation.FIND) {
								// run a find query
								executeFindQuery(conditions, projection);
							}
							else if(FS == Operation.SORT) {
								// run a sort query
								executeSortQuery(projection);
							}
							System.out.println("--------------------------");
							
							// Reset everything for next query 
							FS = Operation.NEITHER;
							currentStep = OCP.NONE;
							conditions.clear();
							query.clear();
						}
					}
		    	}
		    }
			
			lineReader.close();
		} catch (IOException ex) {
			System.err.println(ex);
		}
	}
	
	
	/**
	 * This method runs a find query and edits the global variable query
	 */
	public void executeFindQuery(ArrayList<String> conditions, String projections) {
		String arg1 = null;
		String operator = null;
		int arg2;
		
		int passed = 0;
		
		if(conditions.isEmpty()) {
			System.out.println("Error: there are no conditions");
			return;
		}
		
		String checkConditions = conditions.get(0);
		
		// This means that there are no conditions
		if(checkConditions.equals("Y")) {
			printNoConditions(projections);
		}
		else {
			for(LinkedHashMap<String, Integer> doc : database) {
				for(String a : conditions) {
					String[] b = a.split(" ");
					
					arg1 = b[0];
					operator = b[1];
					arg2 = Integer.parseInt(b[2]);
					
					// it will be null if the current document does not contain the arg1
					// we need to make sure the document passes every condition 
					// if it fails one condition then continue and don't add it
					if(doc.containsKey(arg1)) {
						
						if(operator.equals("=")) {
							if(doc.get(arg1) == arg2) passed++;
						}
						else if(operator.equals(">")) {
							if(doc.get(arg1) > arg2) passed++;
						}
						else if(operator.equals("<")) {
							if(doc.get(arg1) < arg2) passed++;
						}
						
					}
				}
				
				if(passed == conditions.size()) {
					if(query.contains(doc)) {
						; // do nothing 
					} else query.add(doc); 
				}
				
				passed = 0;
			}
			
			printQuery(projections);
		}
		
	}
	
	/**
	 * This method runs a sort query and edits the global variable query
	 */
	public void executeSortQuery(String projection) {
		String arg1 = null;
		String arg2 = null;
		
		String[] a = projection.split(" ");
		
		arg1 = a[0];
		arg2 = a[2];
		
		System.out.println(arg1);
		
		// iterate through the documents 
		for(LinkedHashMap<String, Integer> b : database) {
			// it will be null if the current document does not contain the arg1
			if(b.containsKey(arg1)) {
				query.add(b);
			}
		}
		
		// SELECTION SORT
		int n = query.size();
		LinkedHashMap<String, Integer> c = null;
		
		for(int i = 0; i < n-1; i++) {
			// The minimum element in the unsorted array
			int min_doc = i;
			
			for(int j = i+1; j < n; j++) {
				if(query.get(j).get(arg1) < query.get(min_doc).get(arg1)) {
					min_doc = j;
				}
			}
			
			// Swap the documents
			c = query.get(min_doc);
			query.set(min_doc, query.get(i));
			query.set(i, c);
		}
		// END SELECTION SORT
		
		printSortQuery(arg2);
		
	}
	
	/**
	 * Prints out the sorted query either in order or reverse order 
	 * @param arg2
	 * @param c
	 */
	public void printSortQuery(String arg2) {
		
		if(query.isEmpty()) {
			System.out.println("Empty Output");
			return;
		}
		
		int numEntries = 0;
		int n = query.size();
		// Print either in order or in reverse order 
		System.out.println("[");
		if(arg2.equals("1")) {
			// Prints the list of documents in order
			for(LinkedHashMap<String, Integer> d : query) {
				System.out.print("{ ");
				Set<Entry<String, Integer>> keys = d.entrySet();
				
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					Integer currValue = e.getValue();
					
					if(numEntries > 0) System.out.print(", ");
					System.out.print(currKey + ": \'" + currValue + "\'");
					numEntries++;
				}
				System.out.println("}");
				numEntries = 0;
			}
		}
		// It probably equals -1
		else{
			// Prints the list of documents in reverse order
			for(int i = n-1; i >= 0; --i) {
				System.out.print("{ ");
				
				Set<Entry<String, Integer>> keys = query.get(i).entrySet();
				
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					Integer currValue = e.getValue();
					
					if(numEntries > 0) System.out.print(", ");
					System.out.print(currKey + ": \'" + currValue + "\'");
					numEntries++;
				}
				System.out.println("}");
				numEntries = 0;
			}
		}
		System.out.println("]");
	}
	
	
	/**
	 * This method prints out the query based on what is to be projected
	 */
	public void printQuery(String projection) {
		
		if(query.isEmpty()) {
			System.out.println("Empty Output");
			return;
		}
		
		
		
		String[] projections = projection.split(" ");
		int numEntries = 0;
		
		// iterate through the documents that passed all of the conditions
		System.out.println("[");
		
		// There are conditions but no projection limits 
		if(projection.equals("Z")) {
			for(LinkedHashMap<String, Integer> a : query) {
				System.out.print("{ ");
				Set<Entry<String, Integer>> keys = a.entrySet();
				
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					Integer currValue = e.getValue();
					
					if(numEntries > 0) System.out.print(", ");
					System.out.print(currKey + ": \'" + currValue + "\'");
					numEntries++;
				}
				System.out.println("}");
				numEntries = 0;
			}
		}
		else {
			for(LinkedHashMap<String, Integer> a : query) {
				System.out.print("{ ");
				Set<Entry<String, Integer>> keys = a.entrySet();
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					Integer currValue = e.getValue();
					
					for(int i = 0; i < projections.length; ++i) {
						String currentProjection = projections[i];
						
						// If the current key is within the list of projections then it gets printed 
						if(currKey.equals(currentProjection)) {
							if(numEntries > 0) System.out.print(", ");
							System.out.print(currKey + ": \'" + currValue + "\'");
							numEntries++;
						}
					}
				}
				System.out.println("}");
				numEntries = 0;
			}
		}
		System.out.println("]");
	}
	
	/**
	 * This method prints out the query if the condition is Y, meaning there are no conditions 
	 */
	public void printNoConditions(String projection) {
		String[] projections = projection.split(" ");
		int numEntries = 0;
		
		// This means that there are no conditions and no projection limits so print the whole collection 
		if(projection.equals("Z")) {
			System.out.println("[");
			for(LinkedHashMap<String, Integer> a : database) {
				System.out.print("{ ");
				Set<Entry<String, Integer>> keys = a.entrySet();
				
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					Integer currValue = e.getValue();
					
					if(numEntries > 0) System.out.print(", ");
					System.out.print(currKey + ": \'" + currValue + "\'");
					numEntries++;
				}
				System.out.println("}");
				numEntries = 0;
			}
			System.out.println("]");
		}
		else {
			// No conditions but there are projection limits
			for(LinkedHashMap<String, Integer> a : database) {
				Set<Entry<String, Integer>> keys = a.entrySet();
				
				for(Entry<String, Integer> e : keys) {
					String currKey = e.getKey();
					
					for(int i = 0; i < projections.length; ++i) {
						String currentProjection = projections[i];
						
						// If the current key is within the list of projections then it gets printed 
						if(currKey.equals(currentProjection)) {
							query.add(a);
						}
					}
				}
				numEntries = 0;
			}
			printQuery(projection);
		}
	}

}