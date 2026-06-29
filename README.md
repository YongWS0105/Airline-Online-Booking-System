# Airline-Online-Booking-System
Console-based C++ Airline Booking System using object structs and flat-file data persistence. Simulates secure user login, multi-passenger booking pipelines, and automated fare calculators. Features strict logic validations for dates, passport formats, and payment card profiles, culminating in state-driven check-ins and invoice generation.

## 🛫 Project Description

This repository features a robust, interactive console-based **Airline Online Booking and Flight Management System** built entirely in C++. The application simulates an end-to-end commercial aviation workflow—from structural account registration to real-time itinerary compilation and text-based document rendering. 

Designed with an emphasis on data integrity, the system functions as a modular deterministic state machine. It mandates strict execution rules (e.g., preventing a user from checking into a flight or printing financial transcripts until localized validation states evaluate to positive). 

### ⚙️ Core Subsystems

*   **Secure Authentication Engine**: Features custom credential parsing algorithms, profile data persistence, password complexity evaluation, and runtime duplicate username collision checking.
*   **Dynamic Booking & Modification Kernel**: Supports multi-passenger concurrent booking allocations sharing unified departure and return routes. Includes a real-time modification engine enabling adjustments to flight paths, seat slots, and passenger strings.
*   **Granular Validation Layer**: Leverages strict pattern-matching algorithms to sanitize user data across all entry pipelines, featuring:
    *   *Financial Sanitization*: Validates credit/debit criteria (16-digit sequences, CVV sizes, and expiration patterns) and alphanumeric bank routing profiles.
    *   *Identity Verification*: Enforces custom string parsing for regional telephone structures and global passport layout criteria (6–9 alphanumeric characters).
    *   *Temporal Analysis*: Programmatically restricts trip paths to ensure departure timelines chronologically precede return intervals.
*   **State-Driven Persistence Architecture**: Avoids runtime data volatility by mapping structure items (`struct`) directly to localized flat-file text databases (`.txt`). It updates and checks state flags ("Paid", "Checked") on the fly to govern logical progression through the system.
*   **Enhanced Console Interface**: Integrates specialized ANSI terminal escape sequences to drive user color-coding alongside custom loop-based operational status animation bars.
