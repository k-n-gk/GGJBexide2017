var express = require('express');
var app = express();

var underscore = require('underscore');

var port = process.env.PORT || 3000;

//サーバーの立ち上げ
var http = require('http');

//指定したポートにきたリクエストを受け取れるようにする
var server = http.createServer(app).listen(port, function () {
  console.log('Server listening at port %d', port);
});

var io = require('socket.io').listen(server);

var WebSocketServer = require('ws').Server;
var wss = new WebSocketServer({server:server});

var connections = []; 
wss.on('connection', function (ws) {
  console.log('connect!!');
  connections.push(ws);
  ws.on('close', function () {
    console.log('close');
    connections = connections.filter(function (conn, i) {
      return (conn === ws) ? false : true;
    });
  });
  ws.on('message', function (message) {
    console.log('message:', message);
    connections.forEach(function (con, i) {
      con.send(message);
    });
  });
});

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

var players = {}

app.get('/playstart', function(req, res){
  players[req.query.player] = {}
  res.sendStatus(200);
});

app.get('/position', function(req, res){
  var json = req.query.info || "{}";
  var params = JSON.parse(json);
  var result = {}
  if(params.player == 1){
    var temp = players[2] || {}
    result = underscore.extend({player: 2}, temp.position || {})
    players[1] = {position: {x: params.x, y: params.y,z: params.z,zombie: params.zombie || {}}}
  } else {
    var temp = players[1] || {}
    result = underscore.extend({player: 1}, temp.position || {})
    players[2] = {position: {x: params.x, y: params.y,z: params.z,zombie: params.zombie || {}}}
  }
  res.send(result);
});

app.get('/shoot', function(req, res){
  var params = req.query || {};
  var temp = players[params.player] || {}
  var prev = temp.hit_status || {hit_zombie_id: []}
  var hit_status = {hit_player: params.hit_player, hit_zombie_id: prev.hit_zombie_id.push(params.hit_zombie_id)}

  players[params.player] = {hit_status: hit_status}
  res.sendStatus(200);
});

app.get('/player_action', function(req, res){
  var params = req.query || {};
  var result = {}
  if(params.player == 1){
    var temp = players[2] || {}
    result = underscore.extend({player: 2}, temp.hit_status || {})
    result = underscore.extend(result, temp.sonar || {})
    players[2] = {hit_status: {}, sonar: {}}
  } else {
    var temp = players[1] || {}
    result = underscore.extend({player: 1}, temp.hit_status || {})
    result = underscore.extend(result, temp.sonar || {})
    players[1] = {hit_status: {}, sonar: {}}
  }
  res.send(result);
});

app.get('/sonar', function(req, res){
  var params = req.query || {};
  var temp = players[params.player] || {}
  var sonar = {sonar_position_x: params.x, sonar_position_y: params.y, sonar_position_z: params.z}

  players[params.player] = {sonar: sonar}
  res.sendStatus(200);
});

//サーバーと接続されると呼ばれる
io.on('connection', function(socket){
  console.log('a user connected');
  //接続している、人達(socket)がサーバーにメッセーッジを送った時にcallbackされるイベントを登録
  //第一引数はイベント名
  socket.on('message', function(msg){
    //受け取った人以外でつながっている人全員に送る場合(broadcastを使う)
    //socket.broadcast.emit('message', 'hello');
    //受け取った人含めて全員に送る場合
    //位第一引数のイベント名に対して送る
    //socket.broadcast.emit('message', msg);
    io.emit('message', msg);
    console.log('message: ' + msg);
  });

  //サーバーとの接続が遮断されると呼ばれる
  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});