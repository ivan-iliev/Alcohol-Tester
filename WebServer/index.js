//MADE BY IVAN ILIEV FOR SOFTUNIADA 2020



//Configuring the firebase database ,so that the js can retrieve the data from the db
const firebaseConfig = {
  apiKey: "AIzaSyA9cUiY3pf4cnuvlf2NQMruBD9SlS7O3lY",
  authDomain: "nodemcu-915c6.firebaseapp.com",
  databaseURL: "https://nodemcu-915c6.firebaseio.com",
  projectId: "nodemcu-915c6",
  storageBucket: "nodemcu-915c6.appspot.com",
  messagingSenderId: "989580044936",
  appId: "1:989580044936:web:add1ee96a076709e118d3d",
  measurementId: "G-RQ0CW82YVD"
};
  firebase.initializeApp(firebaseConfig);
  firebase.analytics();

//Making a reference to the db
var database = firebase.database();
//Making ref's to every path of the db
var soberRef = database.ref('Values/Sober/Value');
var lowRef = database.ref('Values/Low/Value'); 
var mediumRef = database.ref('Values/Medium/Value');
var highRef = database.ref('Values/High/Value');
var drunkRef = database.ref('Values/Drunk/Value');  
//Here im telling the ref's to wait for data from type value and then 
//if we've got the data to execute the first function, but if we havent
// got the data to execute the second function
soberRef.on('value',gotDataForSober,errData);
lowRef.on('value',gotDataForLow,errData);
mediumRef.on('value',gotDataForMedium,errData);
highRef.on('value',gotDataForHigh,errData);
drunkRef.on('value',gotDataForDrunk,errData); 

//This a func that gets the retrieved data and puts it in our lists
function gotDataForSober(data){
   
    //this is the data that we have gotten
    var values = data.val();
    //this i an array with all the keys that we have gotten
    var keys = Object.keys(values);
 
    for(var i = 0 ; i < keys.length ; i++){
        var k = keys[i];
        var prom = values[k];
        

        var li = document.createElement("OL");
        var text = document.createTextNode("Value: " + prom);
        li.appendChild(text);
        document.getElementById("soberList").appendChild(li);
        
        
    }
}

//This a func that gets the retrieved data and puts it in our lists
function gotDataForLow(data){

    var values = data.val();
    var keys = Object.keys(values);
 
    for(var i = 0 ; i < keys.length ; i++){
        var k = keys[i];
        var prom = values[k];
    

        var li = document.createElement("OL");
        var text = document.createTextNode("Value: " + prom);
        li.appendChild(text);
        
        document.getElementById("lowList").appendChild(li);
        
    }
}

//This a func that gets the retrieved data and puts it in our lists
function gotDataForMedium(data){
    var values = data.val();
    var keys = Object.keys(values);

   

 
    for(var i = 0 ; i < keys.length ; i++){
        var k = keys[i];
        var prom = values[k];
        console.log(prom);

        var li = document.createElement("OL");
        var text = document.createTextNode("Value: " + prom);
        li.appendChild(text);
        
        document.getElementById("mediumList").appendChild(li);
        
    }
}
//This a func that gets the retrieved data and puts it in our lists
function gotDataForHigh(data){
    var values = data.val();
    var keys = Object.keys(values);


 
    for(var i = 0 ; i < keys.length ; i++){
        var k = keys[i];
        var prom = values[k];

        var li = document.createElement("OL");
        var text = document.createTextNode("Value: " + prom);
        li.appendChild(text);
        
        document.getElementById("highList").appendChild(li);
        
    }
}
//This a func that gets the retrieved data and puts it in our lists
function gotDataForDrunk(data){
    var values = data.val();
    var keys = Object.keys(values);


 
    for(var i = 0 ; i < keys.length ; i++){
        var k = keys[i];
        var prom = values[k];

        var li = document.createElement("OL");
        var text = document.createTextNode("Value: " + prom);
        li.appendChild(text);
        
        document.getElementById("drunkList").appendChild(li);
        
    }
}
//This a func that tells us if we have any type of err
function errData(err){
    console.log("Error");
    console.log(err);
}