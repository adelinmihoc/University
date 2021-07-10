function getEntities1() {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/getAll.php',
            // url: 'http://localhost:8080/api/getAll.jsp',
            url: 'https://localhost:5001/api/getAll',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });
}

function getEntities2(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/getAll.php',
            // url: 'http://localhost:8080/api/getAllFiltered.jsp',
            url: 'https://localhost:5001/api/getAll',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });
}

function addEntity(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/add.php',
            // url: 'http://localhost:8080/api/add.jsp',
            url: 'https://localhost:5001/api/add',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });
}

function deleteEntity(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/delete.php',
            // url: 'http://localhost:8080/api/delete.jsp',
            url: 'https://localhost:5001/api/delete',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });

}

function updateEntity(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/update.php',
            // url: 'http://localhost:8080/api/update.jsp',
            url: 'https://localhost:5001/api/update',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });
}

function fullAuthenticate(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/authentication.php',
            // url: 'http://localhost:8080/api/authentication.jsp',
            url: 'https://localhost:5001/api/authenticate',
            dataType: 'json',
            contentType: 'application/json', // good for asp bad for jsp
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                alert("Invalid credentials!");
                reject(err);
            }
        });
    });
}

function fullRegister(entity) {
    return new Promise(function (resolve, reject) {
        $.ajax({
            type: 'POST',
            // url: 'http://localhost/Servers/php/registration.php',
            // url: 'http://localhost:8080/api/registration.jsp',
            url: 'https://localhost:5001/api/register',
            contentType: 'application/json', // good for asp bad for jsp
            dataType: 'json',
            data: JSON.stringify(entity),
            cache: false,
            success: function (data) {
                resolve(data);
            },
            error: function (err) {
                reject(err);
            }
        });
    });
}
