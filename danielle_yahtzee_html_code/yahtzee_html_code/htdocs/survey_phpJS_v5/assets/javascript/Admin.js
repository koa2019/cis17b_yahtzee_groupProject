var THREE = 3;

function Admin(){
    console.log("Hit Admin Default Constructor");    
    
    this.totalRec = 5; //= this.user.getNumRec(); //get number of records in DB
    this.recSiz = 0;  
    
    // Aggreagte instance of User class
    this.userArr = new Array();
    this.userArr = new User();    
    
    
    // Aggreagte instance of Votes class and create an Array of Votes objects
    // Will hold total votes for each question's answer received
    this.results = new Array(THREE); 
    this.results = new Votes();  
    for(var ii=0; ii < THREE; ii++){
        this.results[ii] = new Votes();
    }
    //this.results.prntVotes();
    
    // Create double pointer. An array of Admin objects
    // Admin **usrArr = nullptr;
    this.usrArr = new Array(this.totalRec);
    this.usrArr = new User(); // Admin*[totalRec];    
    
    for(var i=0; i < this.totalRec; i++){
        this.usrArr[i] = new User(i); // Calls constructor #2        
    }        

    this.readCookie();  // Reset user array with record values read in from binary file
}

//******************************************************************
//                     Read binary file & reset usrArr[]
//******************************************************************
Admin.prototype.readCookie=function(){
    
    console.log("\nHit readCookie()\n");    
    var i = 0;
    var allcookies = [
        {id: 1, name:'Homer', email:'homer@simp.com', password:'Homer123', votes0:'1', votes1:'1', votes2:'1'},
        {id: 2, name:'Marge', email:'marge@simp.com', password:'Marge123',  votes0:'2', votes1:'2', votes2:'2'},
        {id: 3, name:'Lisa', email:'lisa@simp.com', password:'Lisa123',  votes0:'0', votes1:'0', votes2:'0'},
        {id: 4, name:'Bart', email:'bart@simp.com', password:'Bart123',  votes0:'1', votes1:'0', votes2:'0'},
        {id: 5, name:'Ned', email:'ned@flanders.com', password:'Flanders123',  votes0:'1', votes1:'1', votes2:'1'}
    ];
    var stop = allcookies.length;
    //console.log('allcookies.length = ' + stop);
    //console.log(allcookies[i]);
    
    
    // Accumulate the size of each record and the beginning bit location for each record
    while(i < stop){    
       
        this.usrArr[i].setId(allcookies[i].id);  // Set id in User object 
        this.usrArr[i].setName(allcookies[i].name); // Set name in User object   
        this.usrArr[i].setEmail(allcookies[i].email); // Set email in User object 
        this.usrArr[i].setPwrd(allcookies[i].password); // Set password in User object         
        this.usrArr[i].votes.setVoteIndx(0,allcookies[i].votes[0]);  // Read each element in Votes array      
        this.usrArr[i].votes.setVoteIndx(1,allcookies[i].votes[1]);          
        this.usrArr[i].votes.setVoteIndx(2,allcookies[i].votes[2]); 
        this.usrArr[i].setVoteSize(allcookies[i].votes.length); // Set voteSiz in class object 
        //this.usrArr[i].printUser();
        i++; 
    }    
    
    i = (i > this.totalRec) ? i : this.totalRec;
    //this.setResults();               
};


/******************************************************************/ 
//
/******************************************************************/ 
Admin.prototype.setResults=function(){
    
    console.log("Hit setResults()");  
    
    // Reset voting results arrays to zero
    for(var i=0; i < THREE; i++){ 
        this.results[i].setVoteArr(0,0,0);
    }
    
    // Loop through usrArr[]  
    for(var i=0; i < this.totalRec; i++){      
     
        //usrArr[i]->printAllVotes();        
        
        var count = 0;
        
        // Loop through number of questions in survey
        for(var voteIndx=0; voteIndx < THREE; voteIndx++){           
       
                        
            // set this person's vote for question 1, 2, and 3
            //var ans = usrArr[i]->user.votes.getVote(voteIndx); //  vote[0] = ques1Answer           
                                                                //  vote[1] = ques2Answer 
                                                                //  vote[2] = ques3Answer 
            //cout<<"\tvoteIndx = " << voteIndx << " count = " << count << endl;    
            
//            if(voteIndx === count) {                  
//                
//                //if( ans === 1){          // vote[count] = 1 ? QSum[0].vote[0] = +1                   
//                
//                    //cout << " Hit ans == 1\n";
//                    results[voteIndx].increVote(0); 
//                
//                } else if(ans == 2){  //  vote[count] = 2 ? QSum[0].vote[1] = +1
//                    
//                    //cout << " Hit ans == 2\n";
//                    results[voteIndx].increVote(1);
//                
//                } else if(ans === 3){   //  vote[count] = 3 ? QSum[0].vote[2] = +1
//                    
//                    //cout << " Hit ans == 3\n";
//                    results[voteIndx].increVote(2);
//                }
//                else {
//                    console.log("");
//                }
//            }            
            count++;
            
        } // ends voteIndx < THREE        
        //cout<<" After tallying sum \n"; printResults();        
    } // ends i < totalRec 
};



/******************************************************************/ 
//                  Print Survey Results
/******************************************************************/ 
Admin.prototype.printResults=function(){
    
    console.log("\n*****Survey Results*****");
    
    
    // Loop through usrArr[] & print their votes[]     
    for(var i=0; i < this.totalRec; i++){   
        //usrArr[i]->printAllVotes();    
    }
    
    
    //console.log(" a1 a2 a3\n");
    for(var i=0; i < THREE; i++){
        //console.log("   Q" + (i+1) + " total votes[ ");
        this.results[i].prntVotes();
        
    }     
    
    var survey = new Array();
    survey = new Survey();
     
    var tRecFloat = this.totalRec;
    var avg = 0.0;    
    
    // Print results for each question and its answers
//    for(var i=0; i < THREE; i++){ 
//        
//        console.log("\n\n\t  Question " + (i+1) + " results\n\n");
//        console.log(survey.question[i].getQIndx(0));
//             
//        // Print total votes answer 1 received 
//        avg = (results[i].getVote(0)/tRecFloat)*100;
//        console.log(survey.question[i].getQIndx(1) + "  "  
//             + results[i].getVote(0) + " vote(s) "  + avg + "%  ");
//        this.getChart(results[i].getVote(0));
//        
//        
//        // Print total votes answer 2 received 
//        avg = (results[i].getVote(1)/tRecFloat)*100;
//        console.log(survey.question[i].getQIndx(2) + "  " 
//             + results[i].getVote(1) + " vote(s) " + avg + "%  ");
//        this.getChart(results[i].getVote(1));
//        
//        
//        // Print total votes answer 3 received 
//        avg = (results[i].getVote(2)/tRecFloat)*100;
//        console.log(survey.question[i].getQIndx(3) + "  "
//             + results[i].getVote(2) + " vote(s) " + avg + "%  ");
//        this.getChart(results[i].getVote(2));
//    }    
};


/******************************************************************/ 
//              Print histogram
/******************************************************************/ 
Admin.prototype.getChart=function(qSum){  
    var string = "";
    for(var i = 0; i < qSum; i++){        
        string += "*";  
    }
    console.log(string);
};
