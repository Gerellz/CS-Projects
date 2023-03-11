/*****************************************************************
* CSCI 480 - Assignment 1 - Spring 2023
*
* Programmer : Gerald Ellsworth
* Section : 480-1
* TA : Daniel Feller
* Date Due : 2/4/2023
* Purpose : Query and read information from the proc file system.
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

/**************************************************
* Function that reads the /proc/kernel folder
* for information regarding Turing's system.
*
* @param file: The file being read by the function.
* @return: A string containing the information being
*          searched for.
**************************************************/
std::string readKernel(std::string file) {
    std::ifstream input(file);              // Open the file using an input stream

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());  // Accesses the input stream and places it into a buffer string.

    if (!buffer.empty() && buffer[buffer.length() - 1] == '\n')                                     // If the buffer is not empty and the last character is a new line, erase the new line.
        buffer.erase(buffer.length() - 1);

    input.close();                          // Close the file.

    return buffer;
}

/***************************************************
* Function that reads the /proc/cpuinfo file
* for information regarding Turing's system.
*
* @param file: The file being read by the function.
* @param location: The start of the string we're 
*                   looking to find.
* @return: A size_t number that represents the amount
*          of times a string is counted.
***************************************************/
size_t readCpuinfo(std::string file, std::string location) {
    std::ifstream input(file);

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    std::string str = "";

    size_t procsCounter = 0;        // A variable used to count the number of times the string "processor" is found in the file.
    size_t physCounter = 0;         // A variable used to count the number of times the string "physical id" is found in the file.
    size_t pos = 0;                 // A variable used to keep track of the starting position of the substring. Initialized to the start of the file.

    // If statement looks for the string "processor" in the buffer.
    // While parsing through the string until the end, it looks for any time the word "processor"
    // is found. When it is, the counter increments to record how many processors are in the system.
    if (location == "processor") {
        while ((pos = buffer.find(location, pos)) !=std::string::npos) {
            procsCounter++;
            pos += location.length();
        }
        input.close();
        return procsCounter;
    }
    // Secondary if statement that checks if the location is "physical id".
    // If it is, we increment the physCounter to check how many physical chips are in the system.
    // When we have the amount, we divide by the number of cores each processor has to retrieve our answer.
    else if (location == "physical id") {
        while ((pos = buffer.find(location, pos)) !=std::string::npos) {
            physCounter++;
            pos += location.length();
        }
        input.close();
        return physCounter / 4;
    }
    else
        return 0;
}

/*************************************************
* Function that reads the uptime proc file
* 
* @param file: The file being read by the function
* 
* @return: A string containing the current uptime
*          of the system in seconds.
*************************************************/
std::string readUptime(std::string file) {
    std::ifstream input(file);

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    size_t end = buffer.find(" ");                  // Variable to find the first instance of the space delimiter in the string.

    std::string bufTime = buffer.substr(0, end);    // Place the substring which contains the beginning of the file until the delimiter into a new string.

    input.close();                                  // Close the file.

    return bufTime;
}

/****************************************************
* Function that takes the time in seconds and converts
* it into days, hours, minutes, and seconds.
****************************************************/
void readUptimeInDays() {
    int totalTime = stoi(readUptime("/proc/uptime"));       // Convert the uptime from a string to an integer.

    int day = totalTime / (24 * 3600);                      // Find the number of days by dividing the total number of seconds by the number of seconds in a day.
    totalTime = totalTime % (24 * 3600);                    // Get the remainder of that time to be used to find hours, then minutes, then finally seconds.

    int hours = totalTime / 3600;
    totalTime %= 3600;
    
    int minutes = totalTime / 60;
    totalTime %= 60;
    
    int seconds = totalTime;                                // The total remaining time should be however many seconds are left.

    std::cout << "4. Turing has been up for " << day << " days " << hours << " hours " << minutes << " minutes " << seconds << " and seconds. " << std::endl;
}

/*************************************************
* Function to read the cpuinfo stats for
* processor 0.
*
* @param file: The file being read
* @param location: A string that determines which
*                  return value is to be accessed.
*************************************************/
std::string readCpuinfo2(std::string file, std::string location) {
    std::ifstream input(file);

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    std::string cpuInfoStr = "";

    // If the location we look for is prompted as the vendor_id, we look for the vendor id line and extract the string.
    // I added 12 to the starting position of the substring to get to the value right after vendor_id.
    // By doing this, I also have to subtract an extra 12 characters from the ending position to retrieve the correct substring.
    if (location == "vendor") {
        size_t pos = buffer.find("vendor_id");
        size_t end = buffer.find("\n", pos);
        cpuInfoStr = buffer.substr(pos + 12, end - pos - 12);
        input.close();
        return cpuInfoStr;
    }
    // Same as above, the position has to be modified by 13 characters to extract the value after the model name.
    else if (location == "modelname") {
        size_t pos = buffer.find("model name");
        size_t end = buffer.find("\n", pos);
        cpuInfoStr = buffer.substr(pos + 13, end - pos - 13);
        input.close();
        return cpuInfoStr;
    }
    // When looking for the address size, the delimiter changes to a comma.
    // The physical address uses the comma as the ending delimiter.
    else if (location == "physicalsize") {
        size_t pos = buffer.find("address sizes");
        size_t end = buffer.find(",", pos);
        cpuInfoStr = buffer.substr(pos + 16, end - pos - 16);
        input.close();
        return cpuInfoStr;
    }
    // The virtual address uses the comma as the starting point in the substring
    // and the endline as the endpoint of the substring.
    else if (location == "virtualsize") {
        size_t pos = buffer.find(",");
        size_t end = buffer.find("\n", pos);
        cpuInfoStr = buffer.substr(pos + 2, end - pos - 2);
        input.close();
        return cpuInfoStr;        
    }
    else
        return 0;
}
/*************************************************
* Function to read from the /proc/stat file.
* 
* @param file: The file being read by the function
* @param location: A string that determines which
*                  return value is to be accessed.
*************************************************/
int readProcStat(std::string file, std::string location) {
    std::ifstream input(file);

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    size_t pos = buffer.find("cpu5");               // Variable to hold the start of the substring.
    size_t end = buffer.find("\n", pos);            // Variable to hold the end of the substring.

    std::string proc5String = buffer.substr(pos, end - pos);    // Create a substring containing only cpu5's information.

    // If the location requested is the time in user mode
    if (location == "usermode") {
        pos = proc5String.find(" ") + 1;                            // Look for the first space found to get the beginning of user time information.
        end = proc5String.find(" ", pos);                           // Read from the position to the next space found.

        std::string userTime = proc5String.substr(pos, end - pos);  // A new string is created that holds the time spent in user mode (in units of USER_HZ).

        int secUserTime = stoi(userTime) / sysconf(_SC_CLK_TCK);    // The value must be converted to an integer to get the time in seconds.
                                                                    // Divide the time in USER_HZ by a system constant that allows us to find the time in seconds.
        return secUserTime;
    }

    // If the location requested is the time in system mode
    else if (location == "systemmode") {
        for (int i = 0; i < 4; i++)                         // Loop through the spaces until we arrive at the system mode time value.
            pos = proc5String.find(" ", pos) + 1;

        end = proc5String.find(" ", pos);                           // Modify the endpoint to be the space after the system mode time value.
        proc5String.substr(pos, end - pos);                         // Extract the string containing the value.

        std::string sysTime = proc5String.substr(pos, end - pos);   

        int secSysTime = stoi(sysTime) / sysconf(_SC_CLK_TCK);  // The value must be converted to an integer to get the time in seconds.
                                                                // Divide the time in USER_HZ by a system constant that allows us to find the time in seconds.
        return secSysTime;
    }

    // If the location requested is the time spent in the idle task
    else if (location == "idletime") {
        for (int i = 0; i < 5; i++)                         // Loop through the spaces until we arrive at the idle task time value.
            pos = proc5String.find(" ", pos) + 1;
            
        end = proc5String.find(" ", pos);
        proc5String.substr(pos, end - pos);

        std::string idleTime = proc5String.substr(pos, end - pos);

        int secIdleTime = stoi(idleTime) / sysconf(_SC_CLK_TCK);

        return secIdleTime;
    }
    else
        return 0;
}

/****************************************************
* Function that takes the time in seconds and converts
* it into days, hours, minutes, and seconds.
****************************************************/
void readIdleTimeInDays() {
    int totalTime = readProcStat("/proc/stat", "idletime");     // Takes a value from the readProcStat function to be converted.

    int day = totalTime / (24 * 3600);                          // Find the amount of days by dividing by the amount of seconds in a day.
    totalTime = totalTime % (24 * 3600);                        // Leave the remaining amount to be converted to hours, minutes, and seconds.

    int hours = totalTime / 3600;
    totalTime %= 3600;
    
    int minutes = totalTime / 60;
    totalTime %= 60;
    
    int seconds = totalTime;

    std::cout << "4. This processor has been idle for " << day << " days " << hours << " hours " << minutes << " minutes " << seconds << " and seconds. " << std::endl;
}

/*******************************************************
* Function to check the size (in MB) of the swap device.
*
* @param file: The file being read by the function
* @return: An integer with the value of the size of
           the swap device in MB.
*******************************************************/
int checkSwapSize(std::string file) {
    std::ifstream input(file);

    std::string buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    size_t pos = buffer.find("/");                  // Find the beginning of the second line containing the filename
    size_t end = buffer.find("\t", pos);            // Look for the first instance of a tab which leads us to the size amount.

    pos = end + 1;                                  // Skip the first space before the size amount.
    end = buffer.find("\t", pos) + 1;               // Create an end of the substring at the position of the next tab found in the string.

    std::string swapSize = buffer.substr(pos, end - pos);    // Extract the correct value

    int sizeInMB = stoi(swapSize) / 1024;                    // Convert the value to an integer and then divide by 1024 (the amount of KB in a MB).

    return sizeInMB;
}

/******************************
* Main function
* @return: 0 on successful run.
******************************/
int main() {
    // Strings to be used as arguments for functions to read proper proc files.
    std::string cpuInfo = "/proc/cpuinfo";
    std::string cpuUptime = "/proc/uptime";
    std::string processorInfo = "processor";
    std::string physId = "physical id";
    std::string procStat = "/proc/stat";
    std::string procSwaps = "/proc/swaps";

    // Questions A1-A4
    std::cout << "A. Questions about turing's OS:" << std::endl;
    std::cout << "1. The type of turing's OS is " << readKernel("/proc/sys/kernel/ostype") << "." << std::endl;
    std::cout << "2. The hostname is " << readKernel("/proc/sys/kernel/hostname") << "." << std::endl;
    std::cout << "3. The osrelease is " << readKernel("/proc/sys/kernel/osrelease") << "." << std::endl;
    std::cout << "4. The running version is " << readKernel("/proc/sys/kernel/version") << "." << std::endl;

    // Questions B1-B4
    std::cout << "\nB. Questions about turing's processors:" << std::endl;
    std::cout << "1. Turing has " << readCpuinfo(cpuInfo, processorInfo) << " processors." << std::endl;
    std::cout << "2. Turing has " << readCpuinfo(cpuInfo, physId) << " physical multi-core chips." << std::endl;
    std::cout << "3. Turing has been up for " << readUptime(cpuUptime) << " seconds." << std::endl;
    readUptimeInDays();

    // Questions C1-C4
    std::cout << "\nC. For processor 0, answer these questions:" << std::endl;
    std::cout << "1. The vendor is " << readCpuinfo2(cpuInfo, "vendor") << "." << std::endl;
    std::cout << "2. The model name is " << readCpuinfo2(cpuInfo, "modelname") << "." << std::endl;
    std::cout << "3. The physical address size is " << readCpuinfo2(cpuInfo, "physicalsize") << "." << std::endl;
    std::cout << "4. The virtual address size is " << readCpuinfo2(cpuInfo, "virtualsize") << "." << std::endl;

    // Questions D1-D4
    std::cout << "\nD. For processor 5, answer these questions:" << std::endl;
    std::cout << "1. The time (in seconds) that this processor has spent in user mode is " << readProcStat(procStat, "usermode") << "." << std::endl;
    std::cout << "2. The time (in seconds) that this processor has spent in system mode is " << readProcStat(procStat, "systemmode") << "." << std::endl;
    std::cout << "3. This processor has been idle for " << readProcStat(procStat, "idletime") << " seconds." << std::endl;
    readIdleTimeInDays();

    // Question E
    std::cout << "\nE. What is the size of turing's swap device in MB?" << std::endl;
    std::cout << "The size of turing's swap device in MB is " << checkSwapSize(procSwaps) << "." << std::endl;

    return 0;
}
