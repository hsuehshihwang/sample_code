#!/bin/bash
openssl req -new -key client.key -out client.csr -subj "/C=US/ST=State/L=City/O=MyClient/CN=client.example.com"


