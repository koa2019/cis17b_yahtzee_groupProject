// Helper function to show data
function displayData(data) {
    document.getElementById('display-area').innerHTML = JSON.stringify(data, null, 2);
}

// Function to do option 1: Show all users
function showAllUsers() {
    var users = JSON.parse(localStorage.getItem('UserData'));
    displayData(users);    
    window.location.href = './assets/php/selectAll.php';
}

// Function to do option 2: Find one index
function findOneIndex() {
    var index = prompt("Enter the index you want to find:");
    var users = JSON.parse(localStorage.getItem('UserData'));
    if (users && index < users.length) {
        displayData(users[index]);
    }   
    window.location.href = './assets/php/selectById.php';
}


// Function to do option 3: Find by email
function findByEmail() {
    var email = prompt("Enter the email of the user:");
    var users = JSON.parse(localStorage.getItem('UserData'));
    if (users) {
        var user = users.find(user => decodeURIComponent(user.Email) === email); // Changed to user.Email
        displayData(user);
    }
}

// Function to do option 4: Edit hiScore
function editHiScore() {
    var email = prompt("Enter the email of the user:");
    var hiScore = prompt("Enter the new hiScore:");
    var users = JSON.parse(localStorage.getItem('UserData'));
    if (users) {
        var user = users.find(user => decodeURIComponent(user.Email) === email); // Changed to user.Email
        if (user) {
            user.hiScore = hiScore;
            localStorage.setItem('UserData', JSON.stringify(users));
            displayData(users);
        }
    }
}

// Function to do option 5: Delete a User
function deleteUser() {
    var email = prompt("Enter the email of the user:");
    var users = JSON.parse(localStorage.getItem('UserData'));
    if (users) {
        var index = users.findIndex(user => decodeURIComponent(user.Email) === email); // Changed to user.Email
        if (index !== -1) {
            users.splice(index, 1);
            localStorage.setItem('UserData', JSON.stringify(users));
            displayData(users);
        }
    }
}

// Function to do option 6: Update Admin's Profile
function updateAdminProfile() {
    var name = prompt("Enter new name:");
    var email = prompt("Enter new email:");
    var password = prompt("Enter new password:");
    var chekpass = prompt("Confirm password:");
    var hiScore = prompt("Enter new hiScore:");
    var users = JSON.parse(localStorage.getItem('UserData'));
    if (users && users.length > 0) {
        users[0] = {Name: name, Email: email, Password: password, chekPass: chekpass, hiScore: hiScore};
        localStorage.setItem('UserData', JSON.stringify(users));
        displayData(users);
    }
}