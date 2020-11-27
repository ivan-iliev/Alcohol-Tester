let timestampArr = [];
let promilesArr = [];
var months = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'];

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


    var database;

    database = firebase.database();
    var ref = database.ref('CC:50:E3:60:EF:C1');

    
    ref.on('value', gotData, errData);

    function gotData(data){
        //console.log(data.val());
        var dataDB = data.val();
        var keys = Object.keys(dataDB);
        //console.log(keys);
        for(var i = 0;i < keys.length;i++){
            var k = keys[i];
            var promiles = dataDB[k].Promiles;
            var timestamp = dataDB[k].Timestamp;
            
            var date = new Date(timestamp * 1000);

            var time = date.toDateString() + " " +date.toLocaleTimeString();

           
            console.log();
            
            timestampArr.push(time);
            promilesArr.push(promiles);
            
        }
        
    }




    function errData(err){
        console.log("Err!");
        console.log(err);
    }


var ctxBar = document.getElementById('myChart').getContext('2d');
var ctxPie = document.getElementById('myChartPie').getContext('2d');
var colorBackGround = [];
var colorBorder = [];
var dataChart = promilesArr;

for(var i = 0;i<= dataChart.length;i++){
    console.log(dataChart[i]);
    if(dataChart[i]>=0.01 && dataChart[i]<=0.15){

        colorBackGround[i] = 'rgba(75, 192, 192, 0.2)';
        colorBorder[i] = 'rgba(75, 192, 192, 1)';
    }
    if(dataChart[i]>=0.16 && dataChart[i]<=0.3){
        colorBackGround[i]  = 'rgba(255, 206, 86, 0.2)';
        colorBorder[i]  = 'rgba(255, 206, 86, 1)';
    }
    if(dataChart[i]>0.3){
        colorBackGround[i]  = 'rgba(255, 99, 132, 0.2)';
        colorBorder[i]  = 'rgba(255, 99, 132, 1)';
    }
}



var myChartBar = new Chart(ctxBar, {
    type: 'bar',
    data: {
        labels: timestampArr,
        datasets: [{
            label: 'BAC level for given day' ,
            data: dataChart,
            backgroundColor: 'rgba(75, 192, 192, 0.2)',
            borderColor:  'rgba(75, 192, 192, 1)',
            borderWidth: 1
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true
                }
            }]
        }
    }
});

var myChartPie = new Chart(ctxPie, {
    type: 'pie',
    data: {
        labels: timestampArr,
        datasets: [{
            label: 'BAC level for given day',
            data: dataChart,
            backgroundColor: 'rgba(75, 192, 192, 0.2)',
            borderColor:  'rgba(75, 192, 192, 1)',
            borderWidth: 1
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true
                }
            }]
        }
    }
});

