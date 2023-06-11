// Survey Variables
var questions = // 1 question object array. object with 3 keys & 3 data values
        [{
                qq: "Which series do you like the most?",
                answers: ["Star Wars", "The Simpsons", "Harry Potter"]
            },
            {
                qq: "What is your favorite holiday?",
                answers: ["Thanksgiving", "Christmas", "Halloween"]
            },
            {
                qq: "Which dessert is better?",
                answers: ["Apple Pie al Mode", "Red Velvet Cake", "Cheesecake"]
            }
        ];

var qqSize = questions.length;


//*********************************************************
//              Default Constructor
//*********************************************************
function Survey(user) {
    this.showQuestions(user);
    this.isComplete = false;// survey is complete 
}


//*********************************************************               
// ByClassName will return value. ByName will not return a value
//*********************************************************
Survey.prototype.tallySurvey = function (user) {

    console.log("Hit tallySurvey()");
    //user.votes.consoleVotes();

    for (var i = 0; i < qqSize; i++) {

        var qA0 = document.getElementsByClassName('q0');
        var qA1 = document.getElementsByClassName('q1');
        var qA2 = document.getElementsByClassName('q2');

        var value0 = qA0[i].value;
        var value1 = qA1[i].value;
        var value2 = qA2[i].value;

        if (qA0[i].checked) {
            //console.log('value0 = ' value0);
            user.votes.setVoteIndx(0, value0);
        }

        if (qA1[i].checked) {
            //console.log('value1 = ' + value1);
            user.votes.setVoteIndx(1, value1);
        }

        if (qA2[i].checked) {
            //console.log('value2 = ' + value2);
            user.votes.setVoteIndx(2, value2);
        }
    }

    //   End of Survey. Show User's results
    //user.votes.consoleVotes();
    this.setIsComplete(true);    
    this.results(user);
};


Survey.prototype.results = function (user) {
    
    console.log('Hit results()');
    
    if (this.getIsComplete() === true) {  
        document.getElementById('questions-div').style.display = 'none';
        var resultsDiv = document.getElementById('results-div')
        resultsDiv.style.display = 'block';
        
        var string = "User's updated votes = " + user.votes.getVote(0) + ", " + user.votes.getVote(1) + ", " + user.votes.getVote(2);
        resultsDiv.append(string);        
        //alert(string);
        //user.printUser();        
        user.reWrtRecord(); //rewrite user's record in database 
    }
};

//*********************************************************
//               Set Survey member variable
//*********************************************************
Survey.prototype.setIsComplete = function (boolean) {
    this.isComplete = boolean;
};

Survey.prototype.getIsComplete = function (boolean) {
    return this.isComplete;
};


//*********************************************************
//               Write survey to html
//*********************************************************
Survey.prototype.showQuestions = function (user) {

    //alert("Hit showQuestions()");
    console.log("Hit showQuestions()");


    var div = document.getElementById("questions-div");
    var form = document.createElement('form');
    form.setAttribute('action', ' ');
    form.setAttribute('id', 'surveyForm');
    div.appendChild(form);


    // Write each question and its 3 answers to its own html div
    for (var x = 0; x < qqSize; x++) {


        // Create h2 element for each question & append node to HTML by div id  
        var h2 = document.createElement('h2');
        h2.innerHTML = questions[x].qq;
        form.append(h2);

        // Create a div to group each question's answers together
        var divQQ = document.createElement('div');
        divQQ.setAttribute('id', 'q' + x);
        //divQQ.setAttribute('name','q' + x);
        form.appendChild(divQQ);


        var answers = questions[x].answers; //assigns the array of answers of questions[x] to varaible
        var radio = [qqSize];
        var label = [qqSize];

        // Create a label and an input html element for each question
        // Append nodes to HTML by appending variable data value to div id 
        for (var i = 0; i < qqSize; i++) {

            label[i] = this.makeLabel(answers[i], x, i);
            radio[i] = this.makeRadio('checkbox', i, x);
            divQQ.append(radio[i]);
            divQQ.append(label[i]);
        }

        //console.log(h2);
        //console.log(answers);
    }

    // Create & append a submit button
    var surveyBtn = this.makeBtn('button', 'submit', 'submit-survey');
    surveyBtn.setAttribute('onclick', 'survey.tallySurvey(user)');
    form.append(surveyBtn);

    //document.getElementById('submit-survey').addEventListener('click', this.tallySurvey);
};



// USE THESE FOR project 2 > store.cjs
//                if (qA0[i].checked) {
//                    vote0[i] = value0;
//                    console.log('vote0['+i+'] = '+ vote0[i]);
//                }
//                
//                if (qA1[i].checked) {
//                    vote1[i] = value1;
//                    console.log('vote1['+i+'] = '+ vote1[i]);
//                }
//                
//                if (qA2[i].checked) {
//                    vote2[i] = value2;
//                    console.log('vote2['+i+'] = '+ vote2[i]);
//                }
//}




//*********************************************************
//              Make a submit button   
//*********************************************************
Survey.prototype.makeBtn = function (type, val, id) {
    var input = document.createElement('button');
    input.setAttribute('type', type);
    input.setAttribute('id', id);
    input.setAttribute('value', val);
    input.innerHTML = val;
    return input;
};


//*********************************************************
//      Survey display radio button functions
//*********************************************************
Survey.prototype.makeRadio = function (type, val, qIndex) {

    var input = document.createElement('input');
    input.setAttribute('type', type);
    input.setAttribute('class', ('q' + qIndex)); // name attr groups inputs & allows one radio to be selected
    input.setAttribute('id', ('q' + qIndex + 'a' + val));
    input.setAttribute('value', val);
    return input;
};

//*********************************************************
//               
//*********************************************************
Survey.prototype.makeLabel = function (text, qIndex, opt) { //create label html element
    var label = document.createElement('label');
    label.setAttribute('for', "q" + qIndex + "a" + opt);
    label.innerHTML = text;
    return label;
};

//*********************************************************
//               
//*********************************************************
Survey.prototype.showQuizResults = function () {
    var divResults = document.getElementById('results-container');
    var h1 = document.createElement('h1');
    h1.innerHTML = 'Survey Results';
    divResults.append(h1);
};