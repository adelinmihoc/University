function authenticated() {
    if (sessionStorage.getItem("authenticated") !== "true") {
        sessionStorage.setItem("authenticated", "false");
    }
    // sessionStorage.setItem("authenticationType", "none");
    // sessionStorage.setItem("authenticationType", "simple");
    sessionStorage.setItem("authenticationType", "full");
}

function simpleAuthentication() {
    sessionStorage.setItem("username", $('#simpleUsernameInput').val());
    sessionStorage.setItem("authenticated", "true");
    location.reload();
}

function fullAuthentication() {
    const entity = {
        "username": $('#fullUsernameInput').val(),
        "password": $('#fullPasswordInput').val(),
        "size": $('#fullSizeInput').val()
    };
    $.when(fullAuthenticate(entity)).done(function (data) {
        if (data !== null) {
            sessionStorage.setItem("authenticated", "true");
            sessionStorage.setItem("username", $('#fullUsernameInput').val());
        } else {
            sessionStorage.setItem("authenticated", "false");
        }
        location.reload();
    });
}

function fullRegistration() {
    const entity = {
        "username": $('#fullRegisterUsernameInput').val(),
        "password": $('#fullRegisterPasswordInput').val(),
    };
    $.when(fullRegister(entity)).done(function (data) {
        if (data !== null) {
            sessionStorage.setItem("authenticated", "true");
            sessionStorage.setItem("username", $('#fullRegisterUsernameInput').val());
        } else {
            sessionStorage.setItem("authenticated", "false");
        }
        location.reload();
    });
}

function logout() {
    sessionStorage.clear();
    location.reload();
}

