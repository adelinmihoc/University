
async function getEntities1() {
    // const url = 'http://localhost/Servers/php/getAll.php';
    // const url = 'http://localhost:8080/api/getAll.jsp';
    const url = 'https://localhost:5001/api/getAll';
    let response = await fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function getEntities2() {
    // const url = 'http://localhost/Servers/php/getAll.php';
    // const url = 'http://localhost:8080/api/getAll.jsp';
    const url = 'https://localhost:5001/api/getAll';
    let response = await fetch(url, {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function addEntity(entity) {
    // const url = 'http://localhost/Servers/php/add.php';
    // const url = 'http://localhost:8080/api/add.jsp';
    const url = 'https://localhost:5001/api/add';
    let response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(entity),
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function deleteEntity(entity) {
    // const url = 'http://localhost/Servers/php/delete.php';
    // const url = 'http://localhost:8080/api/delete.jsp';
    const url = 'https://localhost:5001/api/delete';
    let response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(entity),
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function updateEntity(entity) {
    // const url = 'http://localhost/Servers/php/update.php';
    // const url = 'http://localhost:8080/api/update.jsp';
    const url = 'https://localhost:5001/api/update';
    let response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(entity),
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function fullAuthenticate(entity) {
    // const url = 'http://localhost/Servers/php/authentication.php';
    // const url = 'http://localhost:8080/api/authentication.jsp';
    const url = 'https://localhost:5001/api/authenticate';
    let response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(entity),
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function fullRegister(entity) {
    // const url = 'http://localhost/Servers/php/registration.php';
    // const url = 'http://localhost:8080/api/registration.jsp';
    const url = 'https://localhost:5001/api/register';
    let response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(entity),
        headers: {
            'Content-Type': 'application/json'
        } // good for asp bad for jsp
    });
    if (!response.ok) {
        alert(response.statusText);
        return null;
    }
    return await response.json();
}

async function getNotification(entity) {

}



