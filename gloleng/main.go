package main

import "crypto/rand"
import "fmt"

// import "golang.org/x/crypto/pbkdf2"
// import "crypto/sha256"
import "crypto/rsa"
import "crypto/x509"
import "github.com/SSSaaS/sssa-golang"

// import "bytes"
import "encoding/pem"

func main() {
	message := "Brams moeder"

	privkey, err := rsa.GenerateKey(rand.Reader, 4096)
	if err != nil {
		panic(err)
	}

	fmt.Println("=====")
	pubkey := &privkey.PublicKey
	fmt.Println("Public:")
	fmt.Println(pubkey)
	fmt.Println("=====")

	cipher, err := rsa.EncryptPKCS1v15(rand.Reader, pubkey, []byte(message))
	if err != nil {
		panic(err)
	}

	friendlyPrivKey := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privkey)}

	pembytes := pem.EncodeToMemory(friendlyPrivKey)

	shares, err := sssa.Create(2, 4, string(pembytes))
	if err != nil {
		panic(err)
	}

	fmt.Println("Shares")
	fmt.Println(len(shares))

	combined, err := sssa.Combine(shares)
	if err != nil {
		panic(err)
	}

	block, _ := pem.Decode([]byte(combined))
	recoveredKey, err := x509.ParsePKCS1PrivateKey(block.Bytes)
	fmt.Println(recoveredKey.PublicKey)
	plain, err := recoveredKey.Decrypt(rand.Reader, cipher, nil)
	fmt.Println(string(plain))

}
