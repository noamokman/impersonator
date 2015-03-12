# impersonator
User impersonation for windows

## Install

```bash
$ npm install --save impersonator
```


## Usage

```javascript
var impersonator = require('impersonator');

var error = impersonator.logon("username", "password", "domain");

if(error) {
  throw error;
}

// this runs with the token of the given user
// fs.read...

impersonator.logoff();

// return to self
```

## API

### impersonator.logon(username, password, domain)
Logon with the given credentials and change the token on the running proccess.

### impersonator.logoff()
Clear the logged on user and return to the original logged on user.

#### License: MIT
#### Author: [Noam Okman](https://github.com/noamokman)
