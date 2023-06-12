// This is the main function, it gets the user information and adds it to variables
function main() {
    var user = document.getElementById("signupUsername").value;
    var email = document.getElementById("signupEmail").value;
    var pass = document.getElementById("signupPassword").value;
    var chekPass= document.getElementById("comparePassword").value; 
}

// Function to set a message for a form with a given type and message
function setFormMessage(formElement, type, message) {
    const messageElement = formElement.querySelector(".form__message");
    messageElement.textContent = message;
    messageElement.classList.remove("form__message--success", "form__message--error");
    messageElement.classList.add(`form__message--${type}`);
}

// Function to set an input error with a given message
function setInputError(inputElement, message) {
    inputElement.classList.add("form__input--error");
    inputElement.parentElement.querySelector(".form__input-error-message").textContent = message;
}

// Function to clear input errors
function clearInputError(inputElement) {
    inputElement.classList.remove("form__input--error");
    inputElement.parentElement.querySelector(".form__input-error-message").textContent = "";
}

// Function to validate login credentials
function validateLogin(username, password) {
    
    let userData = JSON.parse(localStorage.getItem("UserData"));

    let validUser = false;
    let isAdmin = false;
    let currentUserData;

    for(let user of userData) {
        if((user.Name === username || user.Email === username) && user.Password === password) {
            validUser = true;
            currentUserData = user;
            setCurrentPlayer(username);
            if(user === userData[0]) {
                isAdmin = true;
            }
            break;
        }
    }
    if(validUser) {
        // Create a cookie with the user data
        document.cookie = `UserData=${JSON.stringify(currentUserData)}; path=/`;

        if(isAdmin) {
            window.location.href = 'AdminMenuPage.html';
        } else {
            window.location.href = 'ScoreCard.html';
        }
    } else {
        setFormMessage('login', "error", "Username/Email or Password is incorrect, please create an account if you haven't done so.");
    }
}



// Function to set the current player data
function setCurrentPlayer(username) {
    let userData = JSON.parse(localStorage.getItem("UserData"));

    for(let user of userData) {
        if(user.Name === username || user.Email === username) {
            // Found the current player, so set their data
            localStorage.setItem("currentPlayer", JSON.stringify(user));
            break;
        }
    }
}

document.addEventListener("DOMContentLoaded", () => {
    const loginForm = document.querySelector("#login");
    const createAccountForm = document.querySelector("#createAccount");

    document.querySelector("#linkCreateAccount").addEventListener("click", e => {
        e.preventDefault();
        loginForm.classList.add("form--hidden");
        createAccountForm.classList.remove("form--hidden");
    });

    document.querySelector("#linkLogin").addEventListener("click", e => {
        e.preventDefault();
        loginForm.classList.remove("form--hidden");
        createAccountForm.classList.add("form--hidden");
    });

    loginForm.addEventListener("submit", e => {
        e.preventDefault();

        // Get the input username and password
        var username = document.getElementById("loginUsername").value;
        var password = document.getElementById("loginPassword").value;

        // Validate the login with the input username and password
        validateLogin(username, password);
    });


    document.querySelectorAll(".form__input").forEach(inputElement => {
        inputElement.addEventListener("blur", e => {
            if (e.target.id === "signupUsername" && e.target.value.length > 0 && e.target.value.length < 7) {
                setInputError(inputElement, "Username must be at least 10 characters in length");
            }
        });

        inputElement.addEventListener("input", e => {
            clearInputError(inputElement);
        });
    });
});

