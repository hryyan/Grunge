import ssh

def sync():
	client = ssh.SSHClient()
	client.set_missing_host_key_policy(ssh.AutoAddPolicy())
	client.connect("192.168.49.208", 22, "vincent", "tufei")
	stdin, stdout, stderr = client.exec_command('rm /var/www/mysite/templates/index.html')
	sftp = client.open_sftp()

	#Project settings
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\settings.py', '/var/www/mysite/mysite/settings.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\urls.py', '/var/www/mysite/mysite/urls.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\views.py', '/var/www/mysite/mysite/views.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\wsgi.py', '/var/www/mysite/mysite/wsgi.py')
	
	#Templates
	sftp.put('E:\\eclipse\\workspace\\mysite\\templates\\index.html', '/var/www/mysite/templates/index.html')

	#Static
	sftp.put('E:\\eclipse\\workspace\\mysite\\static\\item.css', '/var/www/mysite/static/item.css')

	#Application 1: LightBlogging
	sftp.put('E:\\eclipse\\workspace\\mysite\\messages\\models.py', '/var/www/mysite/messages/models.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\messages\\views.py', '/var/www/mysite/messages/views.py')

	sftp.close()

if __name__ == "__main__":
	sync()