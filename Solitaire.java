package solitaire;

import java.io.IOException;
import java.util.Scanner;
import java.util.Random;

/**
 * This class implements a simplified version of Bruce Schneier's Solitaire Encryption algorithm.
 * 
 * @author RU NB CS112
 */
public class Solitaire {
	
	/**
	 * Circular linked list that is the deck of cards for encryption
	 */
	CardNode deckRear;
	
	/**
	 * Makes a shuffled deck of cards for encryption. The deck is stored in a circular
	 * linked list, whose last node is pointed to by the field deckRear
	 */
	public void makeDeck() {
		// start with an array of 1..28 for easy shuffling
		int[] cardValues = new int[28];
		// assign values from 1 to 28
		for (int i=0; i < cardValues.length; i++) {
			cardValues[i] = i+1;
		}
		
		// shuffle the cards
		Random randgen = new Random();
 	        for (int i = 0; i < cardValues.length; i++) {
	            int other = randgen.nextInt(28);
	            int temp = cardValues[i];
	            cardValues[i] = cardValues[other];
	            cardValues[other] = temp;
	        }
	     
	    // create a circular linked list from this deck and make deckRear point to its last node
	    CardNode cn = new CardNode();
	    cn.cardValue = cardValues[0];
	    cn.next = cn;
	    deckRear = cn;
	    for (int i=1; i < cardValues.length; i++) {
	    	cn = new CardNode();
	    	cn.cardValue = cardValues[i];
	    	cn.next = deckRear.next;
	    	deckRear.next = cn;
	    	deckRear = cn;
	    }
	}
	
	/**
	 * Makes a circular linked list deck out of values read from scanner.
	 */
	public void makeDeck(Scanner scanner) 
	throws IOException {
		CardNode cn = null;
		if (scanner.hasNextInt()) {
			cn = new CardNode();
		    cn.cardValue = scanner.nextInt();
		    cn.next = cn;
		    deckRear = cn;
		}
		while (scanner.hasNextInt()) {
			cn = new CardNode();
	    	cn.cardValue = scanner.nextInt();
	    	cn.next = deckRear.next;
	    	deckRear.next = cn;
	    	deckRear = cn;

		}
	}
	
	/**
	 * Implements Step 1 - Joker A - on the deck.
	 */
	void jokerA() {
		
		// COMPLETE THIS METHOD
		int tempA1 = 0;
		int targetA = 27;
		
		
	
		CardNode front = deckRear.next;
		CardNode temp = front;
		CardNode curr = front.next;
		CardNode prev = deckRear;
		
		
		while (curr.next != null  && targetA != deckRear.next.cardValue){//targetA is not the first 
		
			if (curr.cardValue != targetA && temp.cardValue != targetA){
				if (curr.next == deckRear.next){
					System.out.println("here");
					return;
				}
				
			}
			
			else if( curr.next == deckRear && curr.cardValue == targetA){// if Joker A is the second to last
			System.out.println("2nd to last");
		
			temp.next = deckRear;
			deckRear.next = curr;
			curr.next = front;
			deckRear = curr;
		
			temp = temp.next;
			
			System.out.println("Joker A: ");
			printList(deckRear);
			return;			
			
		}
		else if (curr.next != deckRear && curr.cardValue == targetA && curr.cardValue != deckRear.cardValue){ // if Joker A is in the middle
			System.out.println("middle");
			CardNode extra = curr.next;
			CardNode extra2 = curr.next.next;
			
			temp.next = curr.next;
			extra.next = curr; 
			curr.next = extra2;
			temp = temp.next;
		
			printList(deckRear);

			return;

		}
		else if (curr.next != null && curr.cardValue == targetA && curr == deckRear){
		System.out.println("last");
			CardNode extra = curr.next; 
			CardNode extra2 = curr.next.next; 
			
			temp.next = extra;
			extra.next = curr; 
			curr.next = extra2;
			deckRear = extra;
			temp = temp.next;
			
			
			System.out.println("Joker A: ");
			
			printList(deckRear);

			
			return;
			
		}
		
		
		
		if (curr.next == deckRear && curr.cardValue == targetA){//Joker is in last position
			CardNode extra = prev;
			
			
		}
		
		curr = curr.next;
		temp = temp.next;
		prev =prev.next;

		}
		if (curr.next != null && temp.cardValue == deckRear.next.cardValue && temp.cardValue == targetA){//Joker is the first one in the list
			CardNode extra = curr.next;
			CardNode extra2 = extra.next;
			if (temp.cardValue == targetA){
				
				curr.next = temp;
				temp.next = extra; 
				deckRear.next = curr;
				
		
			}
		}
		else if (curr.next != null && deckRear.cardValue == targetA){//Joker is last
			System.out.println("last");
			CardNode extra = curr.next;
			CardNode extra2 = curr.next.next;
			
			
			
			temp.next = extra;
			extra.next = curr; 
			curr.next = extra2;
			deckRear = extra;
			temp = temp.next;
		
		}
		
		
		
		
	}
	
	/**
	 * Implements Step 2 - Joker B - on the deck.
	 */
	void jokerB() {
	    // COMPLETE THIS METHOD
		int targetB = 28;
		int tempB1 = 0; 
		int tempB2 = 0;
		
		CardNode original = deckRear.next; 
		
		do{
			if (original.cardValue == targetB){//the joker is found
				System.out.println("Joker is found");
			tempB1 = original.next.cardValue;
			tempB2 = original.next.next.cardValue;

			original.next.next.cardValue = targetB;

			original.next.cardValue = tempB2;

			original.cardValue = tempB1; 

			original = original.next.next;
			
		}
		original=original.next;
			
		
			
		}while(original!= deckRear.next);
		
		
		System.out.println("Joker B: ");
		printList(deckRear);
	}
	
	/**
	 * Implements Step 3 - Triple Cut - on the deck.
	 */
	void tripleCut() { //if there are no cards before 27 or after 28???
		// COMPLETE THIS METHOD
		
		int targetA = 27;
		int targetB = 28; 
		
	 
		CardNode temp = deckRear.next;
		CardNode curr = temp.next;
		CardNode front = deckRear.next;
		
		while(curr.cardValue != targetA && curr.next != null){//test case: there is no 27 or 28
			curr = curr.next;
			temp = temp.next;
	
		}
		
		if (curr.cardValue == targetA && curr.next != null){
			CardNode curr2 = curr.next; 
			while(curr2.cardValue != targetB){
				curr2 = curr2.next;
				if (curr2.cardValue == targetB && curr2 == deckRear){//28 is the last card in the deck
					curr = front; 
				}
			}
			if (curr2.cardValue == targetB && curr2.next != null){
			
				CardNode temp2 = curr2.next;
			
				deckRear.next = curr; 
				temp.next = temp2;
				curr2.next = front; 
			
				
				deckRear = temp;
				
				System.out.println(deckRear.cardValue);
				System.out.println("Triple cut: ");
				printList(temp);
			}
		
		}
		
	
	}
	
	/**
	 * Implements Step 4 - Count Cut - on the deck.
	 */
	void countCut() {	//try out test cases	
		// COMPLETE THIS METHOD
		
		int i = 1; 
		CardNode ptr = deckRear;
		CardNode cc3 = null; 
		CardNode cc4 = null;
		
		if (ptr.cardValue == 28){
			ptr.cardValue = 27;
		}

		while (i <= 28){
			ptr = ptr.next;
			if(i== deckRear.cardValue){
				cc3 = ptr; 
				cc4 = ptr.next; 
				
				
			}	
		
			if (ptr.next == deckRear){
			
				CardNode cc5 = ptr;
			
				cc5.next= deckRear.next; 

				deckRear.next = cc4; 
				
				cc3.next= deckRear; 
		
				printList(deckRear);
			}
			
			i ++;
		}
	
		

		
		}
	
	
	/**
	 * Gets a key. Calls the four steps - Joker A, Joker B, Triple Cut, Count Cut, then
	 * counts down based on the value of the first card and extracts the next card value 
	 * as key. But if that value is 27 or 28, repeats the whole process (Joker A through Count Cut)
	 * on the latest (current) deck, until a value less than or equal to 26 is found, which is then returned.
	 * 
	 * @return Key between 1 and 26
	 */
	int getKey() {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		if (deckRear.next.cardValue == 28){
			deckRear.next.cardValue = 27; 
			jokerA();
			jokerB();
			tripleCut();
			countCut();
			
		}
		
		
		int counter = 1; 
		CardNode ptr = deckRear.next; 
		
		jokerA();
		jokerB();
		tripleCut();
		countCut();
		while (counter <= 28){
			if (counter == deckRear.next.cardValue){
				System.out.println("ptr.next cardValue: "+ptr.next.cardValue);
				if (ptr.next.cardValue != 27 && ptr.next.cardValue != 28){
					System.out.println("here");
					CardNode key = ptr.next; 
					System.out.println("KEY: "+key.cardValue);
					counter = 0;
				}	
					jokerA();
					jokerB();
					tripleCut();
					countCut();
					getKey();
			
			}
			ptr= ptr.next;
			counter ++;
		}
	    return -1;
	}
	
	/**
	 * Utility method that prints a circular linked list, given its rear pointer
	 * 
	 * @param rear Rear pointer
	 */
	private static void printList(CardNode rear) {
		if (rear == null) { 
			return;
		}
		System.out.print(rear.next.cardValue);
		CardNode ptr = rear.next;
		do {
			ptr = ptr.next;
			System.out.print("," + ptr.cardValue);
		} while (ptr != rear);
		System.out.println("\n");
	}

	/**
	 * Encrypts a message, ignores all characters except upper case letters
	 * 
	 * @param message Message to be encrypted
	 * @return Encrypted message, a sequence of upper case letters only
	 */
	public String encrypt(String message) {	
		// COMPLETE THIS METHOD
	    // THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
	    return null;
	}
	
	/**
	 * Decrypts a message, which consists of upper case letters only
	 * 
	 * @param message Message to be decrypted
	 * @return Decrypted message, a sequence of upper case letters only
	 */
	public String decrypt(String message) {	
		// COMPLETE THIS METHOD
	    // THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
	    return null;
	}
}
