## To connect to the server using ssh private and public keys

First go to the server using password then
Go to the client and ssh-key-gen and put the private and public keys into /.ssh/keys/id_rsa which have the private key in id_rsa and public in id_rsa.pub
Then go to the server and put the public key just generated into the /.ssh and connect to the server using ssh using private keys from the client.

## SSH Agent:

Donot need everytime to type the passphrase in the client.

Use SSH as a proxy
