package database;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedHashMap;

/**
 * This class creates and sets up a database 
 * 
 * @author Stephen Sottosanti 
 *
 */

public class Database {
	private enum KV{
		Key,
		Value
	}
	
	/**
	 * This method indexes all keywords found in all the input documents. When this
	 * method is done, the keywordsIndex hash table will be filled with all keywords,
	 * each of which is associated with an array list of Occurrence objects, arranged
	 * in decreasing frequencies of occurrence.
	 * 
	 * @param docsFile Name of file that has a list of all the document file names, one name per line
	 * @throws FileNotFoundException If there is a problem locating any of the input files on disk
	 * @return ArrayList returns the dbms after adding the documents
	 */
	public static ArrayList<LinkedHashMap<String, Integer>> createDatabase(String docsFile, ArrayList<LinkedHashMap<String, Integer>> database) 
	{	
		try {
			// Create an instance of a buffer reader to use to read in documents from a file
			BufferedReader lineReader = new BufferedReader(new FileReader(docsFile));
		    String currentLine = null;
		    
		    Integer id = 1;
			
		    while ((currentLine = lineReader.readLine()) != null) {
		    	LinkedHashMap<String, Integer> document = new LinkedHashMap<String, Integer>();
		    	document.put("A", id);
		    	
				addDocument(document, currentLine);
				database.add(document);
				id++;
		    }
			
			lineReader.close();
		} catch (IOException ex) {
			System.err.println(ex);
		}
		
		return database;
	}
	
	
	/**
	 * Takes a document, parses it, and adds the fieldname,value pairs to the database
	 * @param doc
	 * @return
	 */
	private static void addDocument(LinkedHashMap<String, Integer> document, String currentLine)
	{
		KV key_value = KV.Key;
		String fieldname = null;
		Integer value;
		
		String[] fv_pairs = currentLine.split(" ");
		
		for (String a : fv_pairs) {
			if(key_value == KV.Key) {
				fieldname = a.replaceAll(":", "");
				key_value = KV.Value;
			}
			else {
				value = Integer.parseInt(a);
				document.put(fieldname, value);
				
				key_value = KV.Key;
			}
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}