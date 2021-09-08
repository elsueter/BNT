getNetwork();

let TTcontainer = document.getElementById("TruthTable");
var TTnetwork = new vis.Network(TTcontainer);

TTnetwork.on("afterDrawing", function (ctx) {
    var dataURL = ctx.canvas.toDataURL();
    document.getElementById('TTImg').href = dataURL;
});

let Tracontainer = document.getElementById("Traces");
var Tranetwork = new vis.Network(Tracontainer);

Tranetwork.on("afterDrawing", function (ctx) {
    var dataURL = ctx.canvas.toDataURL();
    document.getElementById('TraImg').href = dataURL;
});

let Attcontainer = document.getElementById("Attractors");
var Attnetwork = new vis.Network(Attcontainer);

Attnetwork.on("afterDrawing", function (ctx) {
    var dataURL = ctx.canvas.toDataURL();
    document.getElementById('AttImg').href = dataURL;
});

let UTracontainer = document.getElementById("UniqueTraces");
var UTranetwork = new vis.Network(UTracontainer);

UTranetwork.on("afterDrawing", function (ctx) {
    var dataURL = ctx.canvas.toDataURL();
    document.getElementById('UTraImg').href = dataURL;
});

deleteTraces();

function getNetwork(){
    fetch("/BNT/getNet")
        .then( response =>
        {
            if ( response.status !== 200 )
            {
                console.log( 'Looks like there was a problem. Status Code: ' +
                    response.status );
                return;
            }

            console.log( response.headers.get( "Content-Type" ) );
            return response.json();
        }
        )
        .then( myJson =>
        {
            console.log(myJson);

            document.getElementById("netExp").value = myJson.exp;

            let TTdot = myJson.nodes
            let TTdata = vis.parseDOTNetwork(TTdot);
            TTnetwork.setData(TTdata);
        } )
        .catch( err =>
        {
            console.log( 'Fetch Error :-S', err );
        } );
}

function generateTraces() {
    fetch("/BNT/getSG")
        .then( response =>
        {
            if ( response.status !== 200 )
            {
                console.log( 'Looks like there was a problem. Status Code: ' +
                    response.status );
                return;
            }

            console.log( response.headers.get( "Content-Type" ) );
            return response.json();
        }
        )
        .then( myJson =>
        {
            console.log(myJson);

            let Tradot = myJson.traces;
            let Tradata = vis.parseDOTNetwork(Tradot);
            Tranetwork.setData(Tradata);

            let Attdot = myJson.attractors
            let Attdata = vis.parseDOTNetwork(Attdot);
            Attnetwork.setData(Attdata);

            let UTradot = myJson.uniqueTraces
            let UTradata = vis.parseDOTNetwork(UTradot);
            UTranetwork.setData(UTradata);
        } )
        .catch( err =>
        {
            console.log( 'Fetch Error :-S', err );
        } );
}
function deleteTraces() {
    fetch("/BNT/clearNet")

    Tranetwork.setData();

    Attnetwork.setData();

    UTranetwork.setData();
}
function sendExp(){
    let data = "{ \"exp\":["
    let raw = document.getElementById('netExp').value;
    let processed = raw.replaceAll("\n", '", "')
    processed = processed.substring(0, processed.length-3);
    processed = '"' + processed;
    data += processed;
    data += "]}";

    console.log(data)

    fetch("/BNT/inputNodes", {
            method: 'POST',
            body: data,
        })
        .then( response =>
        {
            if ( response.status !== 200 )
            {
                console.log( 'Looks like there was a problem. Status Code: ' +
                    response.status );
                return;
            }

            console.log( response.headers.get( "Content-Type" ) );
            return response.json();
        }
        )
        .then( myJson =>
        {
            console.log(myJson);
        } )
        .catch( err =>
        {
            console.log( 'Fetch Error :-S', err );
        } );
}
function sendState(){
    let data = "{ \"state\":"
    data += document.getElementById('inputState').value;
    data += "}";

    console.log(data);

    fetch("/BNT/sendS", {
            method: 'POST',
            body: data,
        })
        .then( response =>
        {
            if ( response.status !== 200 )
            {
                console.log( 'Looks like there was a problem. Status Code: ' +
                    response.status );
                return;
            }

            console.log( response.headers.get( "Content-Type" ) );
            return response.json();
        }
        )
        .then( myJson =>
        {
            console.log(myJson);

            let Tradot = myJson.traces;
            let Tradata = vis.parseDOTNetwork(Tradot);
            Tranetwork.setData(Tradata);

            let Attdot = myJson.attractors
            let Attdata = vis.parseDOTNetwork(Attdot);
            Attnetwork.setData(Attdata);

            let UTradot = myJson.uniqueTraces
            let UTradata = vis.parseDOTNetwork(UTradot);
            UTranetwork.setData(UTradata);
        } )
        .catch( err =>
        {
            console.log( 'Fetch Error :-S', err );
        } );
}