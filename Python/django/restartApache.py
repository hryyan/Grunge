import ssh

def restart():
	client = ssh.SSHClient()
	client.set_missing_host_key_policy(ssh.AutoAddPolicy())
	client.connect("192.168.49.208", 22, "root", "tufei19376")
	stdin, stdout, stderr =  client.exec_command('/etc/rc.d/init.d/httpd restart')

if __name__ == "__main__":
	restart()