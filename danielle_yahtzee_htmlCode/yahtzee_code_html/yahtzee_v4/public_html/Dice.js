
function Dice() {   
    //Public properties of the class
    var value = 0;
    alert("Hit Dice(). value = " + value);
}

 //Dice.prototype.roll=function(){
 function roll(){
    //alert("Hit roll()"); 
    value = (1 + (Math.floor(Math.random() * 6)));
    alert("Hit roll(). dice = " + value);
 };


Dice.prototype.getValue=function() {
//function getValue(){
    return value;
};