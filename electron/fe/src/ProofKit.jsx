import React, { Component } from 'react';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TextField from '@material-ui/core/TextField';
import TableRow from '@material-ui/core/TableRow';
import Button from '@material-ui/core/Button';

class ProofKit extends Component {
    state = {
        proof: [],
        lower: 0,
        upper: 100000,
        lowerCheck: 0,
        upperCheck: 0,
    }

    generateProof = (proofKit) => {
        const { lowerProofKit, upperProofKit, secretKey, value } = proofKit;
        const { lower, upper } = this.state;
        this.setState({lowerCheck: lower});
        this.setState({upperCheck: upper});
        fetch(`http://localhost:3001/`, {
            method: 'POST',
            headers: {
              'Accept': 'application/json',
              'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                lowerProofKit,
                upperProofKit,
                secretKey,
                value,
                lower,
                upper,
            }),
        })
        .then((data) => {
            data.json().then(res => {
                console.log(res);
                this.setState({proof: [res.lowerProof, res.upperProof]});
            })
        });
    }

    sendToEvilCorp = (proofKit) => {
        const { lowerProofKit, upperProofKit } = proofKit;
        const lowerProof = this.state.proof[0];
        const upperProof = this.state.proof[1];
        const { lowerCheck, upperCheck } = this.state;
        fetch(`http://localhost:3002/`, {
            method: 'POST',
            headers: {
              'Accept': 'application/json',
              'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                lowerProofKit,
                upperProofKit,
                lowerProof,
                upperProof,
                lowerCheck,
                upperCheck,
            }),
        });
    }

    handleChange = name => event => {
        this.setState({
          [name]: event.target.value,
        });
    };

    renderProof(proofKit) {
        if(this.state.proof.length === 0) {
            return (
                <div></div>
            );
        }

        return (
            <div>
                <br/>
                <br/>
                <hr/>
                <h2>Proofs</h2>
                <Table class="ProofKitTable">
                    <TableBody>
                        <TableRow>
                            <TableCell>Proofs:</TableCell>
                            <TableCell>{this.state.proof[0]}</TableCell>
                        </TableRow>
                        <TableRow>
                            <TableCell>Secret</TableCell>
                            <TableCell>{this.state.proof[1]}</TableCell>
                        </TableRow>
                    </TableBody>
                </Table>
                <br/>
                <form noValidate autoComplete="off">
                    <TextField
                        className="ProofInput"
                        id="lowerBound"
                        label="Lower bound"
                        value={this.state.lowerCheck}
                        onChange={this.handleChange('lowerCheck')}
                        margin="normal"
                        type="number"
                    />
                    <TextField
                        id="upperBound"
                        label="Upper Bound"
                        value={this.state.upperCheck}
                        type="number"
                        className="ProofInput"
                        onChange={this.handleChange('upperCheck')}
                        margin="normal"
                    />  
                </form>
                <br/>
                <Button
                    variant="contained"
                    color="secondary"
                    onClick={() => this.sendToEvilCorp(proofKit)}
                >
                    Send to Evil Corp
                </Button>
            </div>
        );
    }
    
    render() {
        const { proofKit } = this.props;

        return (
            <div>
                <h1>ProofKit {proofKit.name}</h1>
                <Table class="ProofKitTable">
                    <TableBody>
                        <TableRow>
                            <TableCell>Value</TableCell>
                            <TableCell>{proofKit.value}</TableCell>
                        </TableRow>
                        <TableRow>
                            <TableCell>ProofKits</TableCell>
                            <TableCell>{proofKit.lowerProofKit}</TableCell>
                        </TableRow>
                        <TableRow>
                            <TableCell></TableCell>
                            <TableCell>{proofKit.upperProofKit}</TableCell>
                        </TableRow>
                        <TableRow>
                            <TableCell>Secret</TableCell>
                            <TableCell>{proofKit.secretKey}</TableCell>
                        </TableRow>
                    </TableBody>
                </Table>

                <div class="ProofDiv" >
                    <h2>Generate Proof</h2>
                    <form noValidate autoComplete="off">
                        <TextField
                            className="ProofInput"
                            id="lowerBound"
                            label="Lower bound"
                            value={this.state.lower}
                            onChange={this.handleChange('lower')}
                            margin="normal"
                            type="number"
                        />
                        <TextField
                            id="upperBound"
                            label="Upper Bound"
                            value={this.state.upper}
                            type="number"
                            className="ProofInput"
                            onChange={this.handleChange('upper')}
                            margin="normal"
                        />  
                    </form>
                    <br/>
                    <Button
                        variant="contained"
                        color="secondary"
                        onClick={() => this.generateProof(proofKit)}
                        >
                        Generate
                    </Button>
                </div>
                {this.renderProof(proofKit)}
            </div>
        );
    }
}

export default ProofKit;