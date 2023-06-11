/* 
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/ClientSide/javascript.js to edit this template
 */

//this is the main function, it gets the user information and adds it to variables
function main(){
    var user = document.getElementById("signupUsername").value;
    var emal = document.getElementById("signupEmail").value;
    var pass = document.getElementById("signupPassword").value;
    var chekPass= document.getElementById("comparePassword").value;
    
   // let userData = {
   //     username: user,
   //     email: emal,
   //     password: pass,
   //     checkPass: chekPass
   // };
    
   // let userData_Stringify = JSON.stringify(userData);
    
   // localStorage.setItem("UserData",userData_Stringify);
    
   // let userData_UnString = JSON.parse(localStorage.getItem("UserData"));
}


// Function to set a message for a form with a given type and message
function setFormMessage(formElement, type, message) {
    // Select message element within the form
//    const messageElement = formElement.querySelector(".form__message");
//
//    // Set message content
//    messageElement.textContent = message;
//    // Remove existing success and error classes
//    messageElement.classList.remove("form__message--success", "form__message--error");
//    // Add the appropriate class based on the type
//    messageElement.classList.add(`form__message--${type}`);
}

// Function to set an input error with a given message
function setInputError(inputElement, message) {
    // Add error class to input element
    inputElement.classList.add("form__input--error");
    // Set error message for the input element's parent element
    inputElement.parentElement.querySelector(".form__input-error-message").textContent = message;
}

// Function to clear input errors
function clearInputError(inputElement) {
    // Remove error class from input element
    inputElement.classList.remove("form__input--error");
    // Clear error message for the input element's parent element
    inputElement.parentElement.querySelector(".form__input-error-message").textContent = "";
}

// Event listener for when the DOM content is loaded
document.addEventListener("DOMContentLoaded", () => {
    // Select login and create account forms
    const loginForm = document.querySelector("#login");
    const createAccountForm = document.querySelector("#createAccount");
    

    // Event listener for the "Create Account" link click
    document.querySelector("#linkCreateAccount").addEventListener("click", e => {
        e.preventDefault();
        // Hide login form and show create account form
        loginForm.classList.add("form--hidden");
        createAccountForm.classList.remove("form--hidden");
    });

    // Event listener for the "Login" link click
    document.querySelector("#linkLogin").addEventListener("click", e => {
        e.preventDefault();
        // Hide create account form and show login form
        loginForm.classList.remove("form--hidden");
        createAccountForm.classList.add("form--hidden");
    });

    // Event listener for login form submission
//    loginForm.addEventListener("submit", e => {
//        e.preventDefault();
//
//        // Perform your AJAX/Fetch login
//
//        // Set error message for invalid username/password combination
//        setFormMessage(loginForm, "error", "Invalid username/password combination");
//    });

    // Event listener for input field validation
    document.querySelectorAll(".form__input").forEach(inputElement => {
        // Event listener for input field blur event
        inputElement.addEventListener("blur", e => {
            if (e.target.id === "signupUsername" && e.target.value.length > 0 && e.target.value.length < 6) {
                // Set error message for username length
                setInputError(inputElement, "Username must be at least 6 characters in length");
            }
        });

        // Event listener for input field value change
        inputElement.addEventListener("input", e => {
            // Clear input error when value is changed
            clearInputError(inputElement);
        });
    });
});