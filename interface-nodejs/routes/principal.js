var express = require('express')
var Ansible = require('node-ansible');
var yaml = require('write-yaml');
var app = express();
var resultQuery = "test";
module.exports = app;

app.get('/', function(req, res, next) {
	var url = req.url;
	if (url.includes('?')) {
		var data = {local:  {hosts: req.query.ip}};
		yaml('/ansible/inventory/hosts.yml', data, function(err) {
		  console.log("Error writing inventory")
		});
		var command = new Ansible.Playbook().playbook(
				'/ansible/playbook/configure-raspberry').variables({
			fc : req.query.fc,
			sf : req.query.sf,
			bw : req.query.bw,
			cr : req.query.cr
		});
		command.inventory("./ansible/inventory/hosts.yml");
		command.user('pi');
		command.on('stdout', function(data) { console.log(data.toString()); });
		command.on('stderr', function(data) { console.log(data.toString()); });
		command.exec();
	}
	res.render('principal/list', {
		title : 'Principal List',
		data : resultQuery
	});
});