# Credit-Based Auction Application

## Project Overview

The Credit-Based Auction Application is a console-based C++ program that allows users to buy, sell, and bid on items using a Credit Point (CP) system. This application supports functionalities such as member registration, item listings, placing bids, and user ratings, with a focus on security, scalability, and user-friendly interaction.

## Features

### Core Functionalities

**Non-Member (Guest):**

*   View limited item details: name, category, and description.
*   Register as a member with a strong password policy.

**Member:**

*   **Profile Management:** View, update, and top up credit points.
*   **Item Listings:** Create, edit, and remove listings (restrictions apply if bids are placed).
*   **Bidding:**
    *   Search for items by name, category, or credit point range.
    *   View item details, including the highest bid and bidder.
    *   Place bids, ensuring sufficient CP balance.
*   **Ratings & Reviews:**
    *   Rate buyers and sellers after transactions.
    *   View own average ratings and reviews.

**Admin:**

*   Access all member profiles and item listings without restrictions.
*   **Auction Conclusion:**
    *   Automatically update credit points after a successful auction.
    *   Prevent negative credit point balances.

### Advanced Features

*   **Activity Dashboard:** Personalized account overview for logged-in members.
*   **Automatic Bid Limit:** Automatically place bids until a user-defined limit is reached.

## Project Structure

/src
main.cpp           // Entry point for the application
User.h/.cpp        // User class for member and guest functionality
Admin.h/.cpp       // Admin-specific functionality
Item.h/.cpp        // Item class for auction listings
Auction.h/.cpp     // Auction-related operations
/data
users.txt          // Persistent storage for user data
items.txt          // Persistent storage for item data

## Installation

1.  Clone the repository:
    
    ```bash
    git clone [https://github.com/khoilyminh/Credit-based-Auction-Application.git](https://github.com/khoilyminh/Credit-based-Auction-Application.git)
    ```
    
2.  Open the project in your preferred IDE (e.g., Visual Studio, CLion).
    
3.  Build the project to generate the executable file.
    
4.  Run the application from the console or IDE.
    

## Usage

1.  Launch the application.
    
2.  Select your user type:
    
    *   **Guest:** View items or register as a member.
        
    *   **Member:** Log in to access profile, auction listings, and bidding features.
        
    *   **Admin:** Log in to view all member profiles and listings.
        
3.  Follow the prompts to explore features such as creating listings, bidding, and rating.
    

## Data Files

*   **users.txt:** Stores registered user details, including username, password (encrypted), and ratings.
    
*   **items.txt:** Stores auction items with details like name, category, and current bid status.
    

## Contributing

This project uses GitHub for version control. To contribute:

1.  Fork the repository.
    
2.  Create a new branch for your feature:
    
    ```bash
    git checkout -b feature-name
    ```
    
3.  Commit and push your changes:
    
    ```bash
    git commit -m "Add feature description"
    git push origin feature-name
    ```
    
4.  Submit a pull request.
    

## Testing

*   Unit testing is implemented for core functionalities like registration, bidding, and file handling.
    
*   Test cases are included to validate edge conditions, such as insufficient credit points and invalid inputs.
    

## Acknowledgments

*   Instructor: Dr. Ling Huo Chong
    
*   Course: Software Engineering Design (EEET2482) / Advanced Programming Techniques (COSC2082)
    
*   Semester: 3, 2024
    

## License

This project is for educational purposes only as part of the RMIT curriculum. Redistribution is restricted under academic integrity policies.
