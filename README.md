<h4 align="center">

![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/logoPro.png?raw=true)
</h4>

<p align = "center">
	<font size="3">
<b>In the Last assignment we created server and client code <br> in which the client can upload files that contains vectors that are classified and vectors that needs to be classified and the KNN classifier server classifies his vectors based on the classified ones.
 - Using TCP and C++.<br><br>
	Please read all the instructions carefully. </font><br></b>
</p>

## Note
We assume you have a Linux Operating System, with git installed. (to install git on your linux machine open terminal and insert the commend "sudo apt install git", with the command "git --version" you can check that it installed successfully).

## Introduction
In this assignment, We upgraded our server and client files. <br>
The client receives as an input from the user, and acts accordingly. The full description is written later. 
Then, the client sends the server the data he required, all by using multitreading and supporting multiple clients handling by the server and concurrency.

We implemented 13 classes: 
<br>
CLI class, Command class (with different classes that inherits it - UploadDataFile, AlgoSetting, ClassifyData, DisplayResults, DownloadResults, ExitCommand). <br>

DefaultIO class (with 2 classes that inherits it - StandardIO and SocketIO) <br>
Distance class <br>
KNN class <br>
 

We converted distance and Knn to a class in order to enhere to OOP principles. We used method from within the Knn class to calculate the result for the algorithm. <br>
The distances our program can calculate are: 

Euclidean Distance <br>
 Manhatten Distance<br>
 Chebyshev Distance  <br>
 Canberra Distance  <br>
<b> Minkowski Distance -  Using p=2 <br>
</b> <br>

## How To Compile & Run Code
<b>

1. Clone this repo by creating a specific folder in your computer, open terminal in this folder and run this commend:
    ```
    git clone https://github.com/TopazAvraham/ass4
    ```
    Alternatively, you can just download all the files from this repo to your computer, and save them all in that specific folder

2. Open 2 different “terminal” in this specific folder.<br>
3. Run the compilation command:
	```
    make
    ```
	
4. Run this command in one terminal to run the server code:
	```
    ./server.out (para1) (para2)
    ```
	
	where para1 = port number that the server will listen to. <br>
  <br>
  
5. Run this command in second terminal to run the client code:
	```
    ./client.out (para1) (para2)
    ```
	
  where para1 = IP address of the server <br>
	and para2 = Port number of the server <br>
  
6. Now insert an option to the terminal of the client.
  
	<br>
7. The result will be shown on the client's terminal. Enjoy the result. If the option is not 8, The program will go back to 6.

</b>	

## Implementation & Optimizations
	
In this assignment our server can handle many client in parallelism using threads.<br>
When a new client exceutes the program the server sent him this text: <br>

![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/205.png?raw=true)


#### Option 1- Upload CSV 
If the user pressed this option he will be given the option to enter a path to a local CSV file in this computer and after
pressing enter, our client code will send the content of that file to the server. This file that will contain the classified vectors. After sending the file, the server will send to the client "upload complete". If the path is not legal we will print in the user's terminal "invalid input".

This process will be done twice, the first one for the classified vectors and the second one for the vectors the needs to be classified.  
After the 2 files are uploaded we will show the user the main menu again.

![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/204.png?raw=true)


#### Option 2- Algorithm Settings
If the user pressed this option he will be given the option to change the K number of neighbors the algorithm will use, or to change the distance metric the algorithms will be basing its calculations.

First we will show the user the cureent KNN parameters - the K and the distance metric and afterwards he will be given the oppurtunity to change the settings, if he wishes to do so.

If the user will enter wrong parameters for K or for the metric distance, then the server will send him an error indicating that there is an "invalid input for K" or "invalid input for metric" accordingly.

![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/203.png?raw=true)


#### Option 3- Classify Data
If the user pressed this option the server will start the KNN algorithm calculation based on the files uploaded and the current settings of the algorithm.
If the user hasn't uploaded any files, or uploaded only the training file or the test file, the server will send an error to the client, saying he should upload the data.


#### Option 4- Display Results
If the user pressed this option the server will send the client the KNN algorithm calculation results based on the files uploaded and the current settings of the algorithm.

If the user hasn't uploaded any files, or uploaded only the training file or the test file, the server will send an error to the client, saying he should upload the data.

Also, if the user hasn't classified the data, meaning he didn't pressed option 3- classify data before, so the server will send him an error indicating that he needs to classify the data.

![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/202.png?raw=true)


#### Option 5- Download Results
If the user pressed this option he will be given the option to enter a path in his computer in which the program will create a CSV file in that path with the results of the classification inside the file.

If the path is not correct we will show the user an error messege.

If the user hasn't uploaded any files, or uploaded only the training file or the test file, the server will send an error to the client, saying he should upload the data.

Also, if the user hasn't classified the data, meaning he didn't pressed option 3- classify data before, so the server will send him an error indicating that he needs to classify the data.


#### Option 8- Exit
If the user pressed this option we will exit the program, right after releasing all resources as sockets and thread that are beign used.




The excecution is straight forward: we run the client and server code in different terminals. The client asks to connect to the server and the server host assigns him a designated socket and a designated thread. Then, in the client code, we are reading the input from the user, and send it to the server<br><br>
In the server code we calculate the result based on the classes we implemented from previous assignments, using OOP principles.<br><br>
We implemented a distance class where each metric is a different method, and We implemented a Knn class to calculate distance of the given vector from the vectors in the file, to updating the distances accordingly, to bubble sort the vectors from the file based on the distance we just calculated. Then we use a method which calculates from the given K number from the client, what was the most frequent name and returns it, as the Knn algorithm result.
It does that for all the unclassified vectors in the that the client sent.
If needed, the server sends the result to the client using the designated client_socket and thread that was created for him.
<br><br>

#### Optimizations
The Knn algorithm we implemented is not dependent on a specific distance metric, so it can be changed in everypoint during the algorithm. <br>

The output of our Knn calculation can be changed from standard output to any other output option in one line of code. <br>

In the future, we can get other inputs and make other outputs - without dependence on the implementationof the Knn. <br>

The server creates a thread for each new client and therefore, support multithreading. <br>

When the client wants to download the file results, we open a new thread in the client code that will handle the receiveing of the content file from the server and creates the file in the user's desired directory. <br>
Therefore, the user does not need to wait until the file is fully downloaded and executes other options that the programs offers straight away, while the creation of the file is happening on the background.

We used a design pattern called Command in which every command in our program has its own class of type Command. <br>
the Command class defines everthing relevant for the entire commands in our program and explicitly, an abstract execute method for execution.


![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/201.png?raw=true)


This gives us certain advantages:
1. we can put all the different commands into a data structure such as a map or array, and pull the correct command using a key or index and exceute it.
2. We can create more command or inherite existing commands.
3. We seperated the dependency between the invoker (which executes the command) and to one who will be the receiver.


The execute command is being impleneted by each sub class of Command - our different commands in out program.
Additionally, each command has a member string which is the description.


Also, as stated, we cut off the dependency between the command and the output/input source.
Therefore, we implemented a DefaultIo abstract class and a SocketIO class which inherite the class, and use it in order to implement the communication between the server and the client based on sockets.


![alt text](https://github.com/TopazAvraham/IntroductionToCS-University-C-programming/blob/master/Screenshots/200.png?raw=true)





