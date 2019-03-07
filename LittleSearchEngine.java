package search;

import java.io.*;
import java.util.*;

/**
 * This class encapsulates an occurrence of a keyword in a document. It stores the
 * document name, and the frequency of occurrence in that document. Occurrences are
 * associated with keywords in an index hash table.
 * 
 * @author Sesh Venugopal
 * 
 */




class Occurrence {
	/**
	 * Document in which a keyword occurs.
	 */
	String document;
	
	/**
	 * The frequency (number of times) the keyword occurs in the above document.
	 */
	int frequency;
	
	/**
	 * Initializes this occurrence with the given document,frequency pair.
	 * 
	 * @param doc Document name
	 * @param freq Frequency
	 */
	public Occurrence(String doc, int freq) {
		document = doc;
		frequency = freq;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return "(" + document + "," + frequency + ")";
	}
}

/**
 * This class builds an index of keywords. Each keyword maps to a set of newDocs in
 * which it occurs, with frequency of occurrence in each document. Once the index is built,
 * the newDocs can searched on for keywords.
 *
 */
public class LittleSearchEngine {
	
	/**
	 * This is a hash table of all keywords. The key is the actual keyword, and the associated value is
	 * an array list of all occurrences of the keyword in newDocs. The array list is maintained in descending
	 * order of occurrence frequencies.
	 */
	HashMap<String,ArrayList<Occurrence>> keywordsIndex;
	
	/**
	 * The hash table of all noise words - mapping is from word to itself.
	 */
	HashMap<String,String> noiseWords;
	
	/**
	 * Creates the keyWordsIndex and noiseWords hash tables.
	 */
	public LittleSearchEngine() {
		keywordsIndex = new HashMap<String,ArrayList<Occurrence>>(1000,2.0f);
		noiseWords = new HashMap<String,String>(100,2.0f);
	}
	
	/**
	 * This method indexes all keywords found in all the input newDocs. When this
	 * method is done, the keywordsIndex hash table will be filled with all keywords,
	 * each of which is associated with an array list of Occurrence objects, arranged
	 * in decreasing frequencies of occurrence.
	 * 
	 * @param docsFile Name of file that has a list of all the document file names, one name per line
	 * @param noiseWordsFile Name of file that has a list of noise words, one noise word per line
	 * @throws FileNotFoundException If there is a problem locating any of the input files on disk
	 */
	public void makeIndex(String docsFile, String noiseWordsFile) 
	throws FileNotFoundException {
		// load noise words to hash table
		Scanner sc = new Scanner(new File(noiseWordsFile));
		while (sc.hasNext()) {
			String word = sc.next();
			noiseWords.put(word,word);
		}
		
		// index all keywords
		sc = new Scanner(new File(docsFile));
		while (sc.hasNext()) {
			String docFile = sc.next();
			HashMap<String,Occurrence> kws = loadKeyWords(docFile);
			mergeKeyWords(kws);
		}
		
	}

	/**
	 * Scans a document, and loads all keywords found into a hash table of keyword occurrences
	 * in the document. Uses the getKeyWord method to separate keywords from other words.
	 * 
	 * @param docFile Name of the document file to be scanned and loaded
	 * @return Hash table of keywords in the given document, each associated with an Occurrence object
	 * @throws FileNotFoundException If the document file is not found on disk
	 */
	public HashMap<String,Occurrence> loadKeyWords(String docFile) 
	throws FileNotFoundException {
		
		if(docFile == null){
			throw new FileNotFoundException(); 
		}
		
		HashMap <String,Occurrence> document = new HashMap<String, Occurrence>();//hashmap that will store all the keywords from the text
		Scanner temp = new Scanner(new File(docFile)); 
		//String [] x = new String[1000];
		//int i = 0; 
		
		while(temp.hasNext()){//while the document is not over
			//System.out.println(temp.next());
			String line = temp.next();
			System.out.println(line);
			String result = getKeyWord(line);

			
			if(result != null){//it is a keyword, put it in the hash table
				
				if(document.containsKey(result)){//if the document has the keyword already, increase the frequency
					//x[i++] = result; 
					
					
					Occurrence a = document.get(result);
					a.frequency++;
					document.put(result, a);
				}
				else{
					System.out.println("here");
					//x[i++] = result; 
				
				
					Occurrence b = new Occurrence(docFile,1); 
					document.put(result, b);
					//System.out.println("Hash Map: "+Arrays.toString(x));			

				}
				
				
				
			

			}
		
		}
		//System.out.println(Arrays.toString(x));
		System.out.println(document);
		return document;
	}
	
	/**
	 * Merges the keywords for a single document into the master keywordsIndex
	 * hash table. For each keyword, its Occurrence in the current document
	 * must be inserted in the correct place (according to descending order of
	 * frequency) in the same keyword's Occurrence list in the master hash table. 
	 * This is done by calling the insertLastOccurrence method.
	 * 
	 * @param kws Keywords hash table for a document
	 */
	public void mergeKeyWords(HashMap<String,Occurrence> kws) {
		// COMPLETE THIS METHOD
		
		Set<String> keys = kws.keySet();
		for (String key : kws.keySet()){
			if (!keywordsIndex.containsKey(key)){
				ArrayList<Occurrence> occs = new ArrayList<Occurrence>();
				occs.add(kws.get(key));
				keywordsIndex.put(key, occs);
			}else{
				keywordsIndex.get(key).add(kws.get(key));
				insertLastOccurrence(keywordsIndex.get(key));
				keywordsIndex.put(key, keywordsIndex.get(key));
			}
		}
		
		System.out.println("KeywordIndex: "+keywordsIndex);

				
			
		}
	
	/**
	 * Given a word, returns it as a keyword if it passes the keyword test,
	 * otherwise returns null. A keyword is any word that, after being stripped of any
	 * TRAILING punctuation, consists only of alphabetic letters, and is not
	 * a noise word. All words are treated in a case-INsensitive manner.
	 * 
	 * Punctuation characters are the following: '.', ',', '?', ':', ';' and '!'
	 * 
	 * @param word Candidate word
	 * @return Keyword (word without trailing punctuation, LOWER CASE)
	 */
	public String getKeyWord(String word) {
		
		word = word.toLowerCase();
		
		if(noiseWords.containsKey(word)){
			System.out.println(" "+word+" "+" :NOISEWORD");
			return null;
		}
		//If punctuation is at the end
		int x = word.length()-1; 
		if(Character.isLetter(word.charAt(x)) == false){
			if(word.charAt(x) == '.' || word.charAt(x) == ',' || word.charAt(x) == '?'|| word.charAt(x) == ':'|| word.charAt(x) == ';'|| word.charAt(x) == '!'){
				word = word.substring(0, x);
				return getKeyWord(word);
			}
			
		}
		//If punctuation is in the middle
		int count = 0;
		while(count < word.length()){
				if(Character.isLetter(word.charAt(count))==false){
					System.out.println(" "+word+" "+": NULL");
					return null; 
					}
				
				count++;
				
				
		}
		
		System.out.println("FINAL: "+word);
		return word;
	
	}
	
	/**
	 * Inserts the last occurrence in the parameter list in the correct position in the
	 * same list, based on ordering occurrences on descending frequencies. The elements
	 * 0..n-2 in the list are already in the correct order. Insertion of the last element
	 * (the one at index n-1) is done by first finding the correct spot using binary search, 
	 * then inserting at that spot.
	 * 
	 * @param occs List of Occurrences
	 * @return Sequence of mid point indexes in the input list checked by the binary search process,
	 *         null if the size of the input list is 1. This returned array list is only used to test
	 *         your code - it is not used elsewhere in the program.
	 */
	public ArrayList<Integer> insertLastOccurrence(ArrayList<Occurrence> occs) {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		
		
		ArrayList<Integer> final_result = new ArrayList<Integer>();
		
		int size = occs.size();
		int Low = 0;
		int High = size - 2;
		int Middle;
		int temp = occs.get(size).frequency;
		
		if(size == 1){ //base case
			return null;
		}
		
		while (Low < High){ //similar to mergesort
			Middle = (Low + High)/2;
			final_result.add(Middle);
			if (occs.get(Middle).frequency == occs.get(occs.size() - 1).frequency){
				Low = Middle;
				High = Middle;
				break;
			}
			else if (occs.get(Middle).frequency > occs.get(occs.size() - 1).frequency){
				Low = Middle + 1;
			}
			else{
				High = Middle;
			}
		}
				
		if (temp > occs.get(Low).frequency){
			occs.add(Low, occs.remove(occs.size() - 1));
		}
		
		else{
			occs.add(Low + 1, occs.remove(occs.size() - 1));
		}
		
		System.out.println(" : "+final_result);
		return final_result;
		}
		
	
	/**
	 * Search result for "kw1 or kw2". A document is in the result set if kw1 or kw2 occurs in that
	 * document. Result set is arranged in descending order of occurrence frequencies. (Note that a
	 * matching document will only appear once in the result.) Ties in frequency values are broken
	 * in favor of the first keyword. (That is, if kw1 is in doc1 with frequency f1, and kw2 is in doc2
	 * also with the same frequency f1, then doc1 will appear before doc2 in the result. 
	 * The result set is limited to 5 entries. If there are no matching newDocs, the result is null.
	 * 
	 * @param kw1 First keyword
	 * @param kw1 Second keyword
	 * @return List of NAMES of newDocs in which either kw1 or kw2 occurs, arranged in descending order of
	 *         frequencies. The result size is limited to 5 newDocs. If there are no matching newDocs,
	 *         the result is null.
	 */
	public ArrayList<String> top5search(String kw1, String kw2) {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		ArrayList<String> newDocs = new ArrayList<String>();
		ArrayList<Occurrence> One = null;
		ArrayList<Occurrence> Two = null;
		
		
		//base cases
		if (keywordsIndex.get(kw1) != null){
			One = keywordsIndex.get(kw1);
		}
		
		if (keywordsIndex.get(kw2) != null){
			Two = keywordsIndex.get(kw2);
		}
		
		if (One == null && Two == null){
			return newDocs;
		}
		
		
		else if (One != null && Two == null){
			int index = 0;
			while (newDocs.size() < 5 && index < One.size()){
				if (!newDocs.contains(One.get(index))){
					newDocs.add(One.get(index).document);
				}
			index++;
			}
		}
		
		
		else if (Two != null && One == null){
			int index = 0;
			while (newDocs.size() < 5 && index < Two.size()){
				if (!newDocs.contains(Two.get(index))){
					newDocs.add(Two.get(index).document);
				}
			index++;
			}
		}
		
		
		else{
			int First = 0, Second = 0;
			while (First < One.size() && Second < Two.size() && newDocs.size() < 5){
				if (One.get(First).frequency > Two.get(Second).frequency){
					if (!newDocs.contains(One.get(First).document)){
						newDocs.add(One.get(First).document);
					}
				First++;
				}
				else if (One.get(First).frequency < Two.get(Second).frequency){
					if (!newDocs.contains(Two.get(Second).document)){
						newDocs.add(Two.get(Second).document);
					}
				Second++;
				}
				else{
					if (!newDocs.contains(One.get(First).document)){
						newDocs.add(One.get(First).document);
					}
					if (newDocs.size() < 5 && !newDocs.contains(Two.get(Second).document)){
						newDocs.add(Two.get(Second).document);
					}
				First++;
				Second++;
				}
			}
			
			if (First == One.size()){
				while (Second < Two.size() && newDocs.size() < 5){
					if (!newDocs.contains(Two.get(Second).document)){
						newDocs.add(Two.get(Second).document);
					}
				Second++;
				}
			}
			
			if (Second == newDocs.size()){
				while (First < One.size() && newDocs.size() < 5){
					if (!newDocs.contains(One.get(First).document)){
						newDocs.add(One.get(First).document);
					}
				First++;
				}
			}
		}
		System.out.println(newDocs);
		return newDocs;
		}
}
