import React, { Component } from 'react';
import SplitPane from 'react-split-pane';
import './App.css';
import ProofKit from './ProofKit';
import ProofKitList from './ProofKitList';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import IconButton from '@material-ui/core/IconButton';
import AddIcon from '@material-ui/icons/Add';

class App extends Component {
	state = {
		consoleText: "",
		proofKits: [
			{
				name: "",
				description: "",
				value: 0,
				lowerProofKit: "",
				upperProofKit: "",
				secretKey: "",
				logo: "",
			}
		],
		selected: 0,
	}

	componentDidMount() {
		fetch('http://localhost:3001/items')
		.then(data => {
			data.json().then(res => {
				this.setState({proofKits: res});
			})
		})
	}

	changeSelected = (index) => {
		this.setState({selected: index});
	}

	addText(text) {
		this.setState((state) => {consoleText: `${state.consoleText}\n${text}`})
	}

	render() {
		return (
			<div className="App">
				<AppBar position="static" color="default" className="Header">
					<Toolbar>
						<div class="floatLeft">
						<Typography variant="title" color="inherit">
							Pretty Good Data Storage
						</Typography>
						</div>
						<div class="floatRight">
						<IconButton
							color="inherit"
						>
							<AddIcon />
						</IconButton>
						</div>
					</Toolbar>
				</AppBar>
				<SplitPane split="vertical" defaultSize="40%">
					<ProofKitList items={this.state.proofKits} selected={this.state.selected} change={this.changeSelected} />
					<ProofKit proofKit={this.state.proofKits[this.state.selected]} />
				</SplitPane>
			</div>
		);
	}
}

export default App;
