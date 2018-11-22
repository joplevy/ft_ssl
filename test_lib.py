import os

os.system("make")
os.system("mkdir -p tmp")
for fname in os.listdir("vectors"):
	print("processing vectors/" + fname + " (no output = no diff)")
	os.system("./ft_ssl md5 -r vectors/" + fname + " > tmp/my_md5 \
	&& openssl md5 -r vectors/" + fname + " > tmp/sys_md5 \
	&& diff tmp/my_md5 tmp/sys_md5")
	os.system("./ft_ssl sha256 -r vectors/" + fname + " > tmp/my_sha256 \
	&& openssl sha256 -r vectors/" + fname + " > tmp/sys_sha256 \
	&& diff tmp/my_sha256 tmp/sys_sha256")