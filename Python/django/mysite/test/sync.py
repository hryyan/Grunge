import ssh

def sync():
	client = ssh.SSHClient()
	client.set_missing_host_key_policy(ssh.AutoAddPolicy())
	client.connect("192.168.49.208", 22, "vincent", "tufei")
	sftp = client.open_sftp()
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\settings.py', '/var/www/mysite/mysite/settings.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\urls.py', '/var/www/mysite/mysite/urls.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\views.py', '/var/www/mysite/mysite/views.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\mysite\\wsgi.py', '/var/www/mysite/mysite/wsgi.py')
	sftp.put('E:\\eclipse\\workspace\\mysite\\templates\\index.html', '/var/www/mysite/templates/index.html')
	sftp.close()

if __name__ == "__main__":
	sync()