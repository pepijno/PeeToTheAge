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
    }

    generateProof = () => {
        const params = "?lowerProofKit=yNWhxVy9ahj/VHwXzPnjZ2yYakzzCLTsz7lJIxkizZ0=&upperProofKit=Yugfjn2dgYuhdb0IQs5N6IEW4CgxDgyJ6MPc0zexsfY=&secretKey=T5SjWJGHClPk8aZRNXRAO2QvH2Cibfv5ZGZlkOaeIIE=&value=2345&lower=56&upper=10000";
        fetch(`http://localhost:3001/${params}`)
        .then((data) => {
            data.json().then(res => {
                console.log(res);
                this.setState({proof: [res.lowerProof, res.upperProof]});
            })
        });
    }

    renderProof() {
        if(this.state.proof.length == 0) {
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
                <br/>
                <Button
                    variant="contained"
                    color="secondary"
                    onClick={() => this.generateProof()}
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
                            <TableCell>{proofKit.lowerProofKit}</TableCell>
                        </TableRow>
                        <TableRow>
                            <TableCell>Secret</TableCell>
                            <TableCell>U{proofKit.secretKey}</TableCell>
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
                            value="1"
                            onChange={() => {return null;}}
                            margin="normal"
                            type="number"
                        />
                        <TextField
                            id="upperBound"
                            label="Upper Bound"
                            value="1"
                            type="number"
                            className="ProofInput"
                            margin="normal"
                        />  
                    </form>
                    <br/>
                    <Button
                        variant="contained"
                        color="secondary"
                        onClick={() => this.generateProof()}
                        >
                        Generate
                    </Button>
                </div>
                {this.renderProof()}
            </div>
        );
    }
}

export default ProofKit;