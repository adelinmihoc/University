function displayContent() {
    if (sessionStorage.getItem("authenticationType") === "none") {
        $('#mainWrapper').show();
        $('#simpleLoginFormWrapper').hide();
        $('#fullLoginFormWrapper').hide();
    } else if (sessionStorage.getItem("authenticationType") === "simple") {
        if (sessionStorage.getItem("authenticated") === "false") {
            $('#mainWrapper').hide();
            $('#simpleLoginFormWrapper').show();
            $('#fullLoginFormWrapper').hide();
        } else {
            $('#mainWrapper').show();
            $('#simpleLoginFormWrapper').hide();
            $('#fullLoginFormWrapper').hide();
        }
    } else {
        if (sessionStorage.getItem("authenticated") === "false") {
            $('#mainWrapper').hide();
            $('#simpleLoginFormWrapper').hide();
            $('#fullLoginFormWrapper').show();
        } else {
            $('#mainWrapper').show();
            $('#simpleLoginFormWrapper').hide();
            $('#fullLoginFormWrapper').hide();
        }
    }
}


function populateTable() {

    let array = sessionStorage.getItem('popular');
    array = JSON.parse(array);
    if (array === null) {
        array = [];
    }
    array.push($('#wordInput').val());
    sessionStorage.setItem('popular', JSON.stringify(array));


    const entity = {
        "word": $('#wordInput').val()
    }
    $.when(getEntities2(entity)).done(function (r1) {
        // displayInterleavedArrays(r1, r1);

        displaySimpleArray(r1);

        // paginateTable();
    });
}


function displaySimpleArray(r1) {
    $('#recordTableBody').empty();
    $.each(r1, function (i, item) {
        $('#recordTableBody').append(
            $('<tr onclick="rowClick(this)">').append(
                $('<td>').text(item.id),
                $('<td>').text(item.userid),
                $('<td>').text(item.filename),
                $('<td>').text(item.filecontent),
                $('<td>').text(item.size),
                $('<td>').text(item.apparitions),
            )
        );
    });
}

function searchButtonHandler() {
    const entity = {
        "word": $('#wordInput')
    }
}


function addButtonHandler() {
    const entity = {
        "title": $('#titleInput').val(),
        "genre": $('#genreInput').val()
    };
    $.when(addEntity(entity)).done(function () {
        location.reload();
    });
}


function deleteButtonHandler() {
    const entity = {
        "id": $('#idInput').val(),
    };
    $.when(deleteEntity(entity)).done(function () {
        location.reload();
    });
}


function updateButtonHandler() {
    const entity = {
        "id": $('#idInput').val(),
        "title": $('#titleInput').val(),
        "genre": $('#genreInput').val()
    };
    $.when(updateEntity(entity)).done(function () {
        location.reload();
    });
}


function rowClick(x) {
    $('#idInput').val(x.cells[0].textContent);
    $('#titleInput').val(x.cells[1].textContent);
    $('#genreInput').val(x.cells[2].textContent);
}


function paginateTable() {
    $('#recordTable tbody tr').hide();
    $('#recordTable').after('<div id="nav"></div>');
    let rowsShown = 5;
    let rowsTotal = $('#recordTable tbody tr').length;
    let numPages = rowsTotal/rowsShown;
    for(let i = 0;i < numPages;i++) {
        let pageNum = i + 1;
        $('#nav').append('<a href="#" rel="'+i+'">'+pageNum+'</a> ');
    }
    $('#recordTable tbody tr').hide();
    $('#recordTable tbody tr').slice(0, rowsShown).show();
    $('#nav a:first').addClass('active');
    $('#nav a').bind('click', function(){
        $('#nav a').removeClass('active');
        $(this).addClass('active');
        let currPage = $(this).attr('rel');
        let startItem = currPage * rowsShown;
        let endItem = startItem + rowsShown;
        $('#recordTable tbody tr').css('opacity','0.0').hide().slice(startItem, endItem).
        css('display','table-row').animate({opacity:1}, 300);

        // get elements displayed in current table
        let table = document.getElementById('recordTable');
        for (let r = startItem + 1, n = endItem; r <= n && r < table.rows.length; r++) {
            // console.log(table.rows[r].cells[2].innerHTML);
        }
    });

}


function displayInterleavedArrays(r1, r2) {
    // r1 may contain different objects from r2

    let n1 = r1.length;
    let n2 = r2.length;

    let i = 0;
    for (i; i < Math.min(n1, n2); i++) {
        $('#recordTableBody').append(
            $('<tr onclick="rowClick(this)">').append(
                $('<td>').text(r1[i].id),
                $('<td>').text(r1[i].title),
                $('<td>').text(r1[i].genre)
            ),
            $('<tr onclick="rowClick(this)">').append(
                $('<td>').text(r2[i].id),
                $('<td>').text(r2[i].title),
                $('<td>').text(r2[i].genre)
            )
        );
    }

    while (i < n1) {
        $('#recordTableBody').append(
            $('<tr onclick="rowClick(this)">').append(
                $('<td>').text(r1[i].id),
                $('<td>').text(r1[i].title),
                $('<td>').text(r1[i].genre)
            )
        );
        i++;
    }
    while (i < n2) {
        $('#recordTableBody').append(
            $('<tr onclick="rowClick(this)">').append(
                $('<td>').text(r2[i].id),
                $('<td>').text(r2[i].title),
                $('<td>').text(r2[i].genre)
            )
        );
        i++;
    }
}

function getMostPopular() {
    let array = sessionStorage.getItem('popular');
    array = JSON.parse(array);
    if (array === null) {
        array = [];
    }
    var map = frequencyMap(array);
    var word = '';
    if (map === null) {
        word = 'no searched words so far';
    } else {
        word = map[0];
    }
    $('#popularWord').empty();
    $('#popularWord').append(
      $('<p>').text(word)
    );
}

function frequencyMap(array) {
    if(array.length === 0){
        return null;
    }
    let map = {};
    for (let i = 0; i < array.length; i++) {
        let elem = array[i];
        if (map[elem] == null) {
            map[elem] = 1;
        } else {
            map[elem]++;
        }
    }

    // most occurrences first
    map = Object.keys(map).sort(function (a,b) {
        return map[a] - map[b];
    }).reverse();

    // least occurrences first
    // map = Object.keys(map).sort(function (a,b) {
    //     return map[a] - map[b];
    // });
    return map;
}


