# Credit-Based Auction Application

## Project Overview

The Credit-Based Auction Application is a console-based C++ program that allows users to buy, sell, and bid on items using a Credit Point (CP) system. This application supports functionalities such as member registration, item listings, placing bids, and user ratings, with a focus on security, scalability, and user-friendly interaction.

## Features

### Core Functionalities

**Non-Member (Guest):**

-   View limited item details: name, category, and description.
-   Register as a member with a strong password policy.

**Member:**

-   **Profile Management:** View, and top up credit points.
-   **Item Listings:** Create, and remove listings (restrictions apply if bids are placed).
-   **Bidding:**
    -   Search for items by name, category, or credit point range.
    -   View item details, including the highest bid.
    -   Place bids, ensuring sufficient CP balance.
-   **Ratings & Reviews:**
    -   Rate buyers and sellers after transactions.
    -   View own average ratings and reviews.

**Admin:**

-   Access all member profiles and item listings without restrictions.
-   **Auction Conclusion:**
    -   Automatically update credit points after a successful auction.
    -   Prevent negative credit point balances.

### Advanced Features

-   **Activity Dashboard:** Personalized account overview for logged-in members.
-   **Automatic Bid Limit:** Automatically place bids until a user-defined limit is reached.

## Project Structure

`./src`: The source of the whole project.

`./data`: The directory where data of the application will be stored.

`./bin`: The directory where the binary file for execution will be store

## Execution on Windows OS (Windows 10/11)

The application was compiled and tested using `g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0` on `Windows 10 Pro version 22H2 build 19045.5247`.

Please follow the instructions to compile and execute the project:

1. Make sure you are at the root directory of the project and you could see `./src` directory.

2. Use this command to compile and run:

    ```powershell
    .\run.ps1
    ```

3. (Optional) If the problem **"cannot be loaded because running scripts is disabled on this system. For more information, see about_Execution_Policies at https:/go.microsoft.com/fwlink/?LinkID=135170."** appear, please run the following commands:

    - Run this command with Administrator Powershell:

    ```
    Set-ExecutionPolicy RemoteSigned
    ```

    - After you finish compiling and running the application, use this command to set to **strict** again:

    ```
    Set-ExecutionPolicy Restricted
    ```

## Execution on MacOS/Linux:

The application was compiled and tested using `g++ (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0` on `Ubuntu 20.04.6 LTS` and `Apple clang version 15.0.0 (clang-1500.3.9.4)` on `macOS Sonoma 14.5`.

1. Make sure you are at the root directory of the project and you could see `./src` directory.

2. Use this command to compile:

    ```bash
    ./compile.sh && ./run.sh
    ```

3. (Optional) In case of nothing happend due to file execution restriction, please using bellow command with sudo permission and re-run step 2:

    ```bash
    chmod ./compile.sh 777 && chmod ./run.sh 777
    ```

## Usage

1.  Launch the application.
2.  Select your user type:

    -   **Guest:** View items or register as a member.
    -   **Member:** Log in to access profile, auction listings, and bidding features.
    -   **Admin:** Log in to view all member profiles and listings.

3.  Follow the prompts to explore features such as creating listings, bidding, and rating.

## Testing

-   Unit testing is implemented for core functionalities like registration, bidding, and file handling.
-   Test cases are included to validate edge conditions, such as insufficient credit points and invalid inputs.

## Acknowledgments

-   **Instructor:** Dr. Ling Huo Chong
-   **Course**: Software Engineering Design (EEET2482) / Advanced Programming Techniques (COSC2082)
-   **Semester**: 3, 2024

## License

This project is for educational purposes only as part of the RMIT curriculum. Redistribution is restricted under academic integrity policies.
