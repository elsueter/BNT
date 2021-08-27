getNetwork();

let TTcontainer = document.getElementById("TruthTable");
var TTnetwork = new vis.Network(TTcontainer);

let Tracontainer = document.getElementById("Traces");
var Tranetwork = new vis.Network(Tracontainer);

let Attcontainer = document.getElementById("Attractors");
var Attnetwork = new vis.Network(Attcontainer);

let UTracontainer = document.getElementById("UniqueTraces");
var UTranetwork = new vis.Network(UTracontainer);

deleteTraces();

let TTdata = vis.parseDOTNetwork("dinetwork {node[shape=circle] edge [length=100, color=white, fontcolor=black];B->A; C->A; C->B[arrowhead=box]; A->C[arrowhead=box]}")
TTnetwork.setData(TTdata);

function getNetwork(){
    fetch("/getNet")
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
        } )
        .catch( err =>
        {
            console.log( 'Fetch Error :-S', err );
        } );
}

function generateTraces() {
    fetch("/getSG")
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
    fetch("/clearNet")

    Tranetwork.setData();

    Attnetwork.setData();

    UTranetwork.setData();
}
function sendState(){
    let data = "{ \"state\":"
    data += document.getElementById('inputState').value;
    data += "}";

    console.log(data);

    fetch("/sendS", {
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