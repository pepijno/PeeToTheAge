import React, { Component } from 'react';
import Images from './Images';

class ProofKitListItem extends Component{
    renderImage(logo) {
        if(logo === 'tesla') {
            return Images.tesla;
        }

        return Images.abn;
    }

    render() {
        const { selected, proofKit, index, change } = this.props;

        let id = "";
        if(selected) {
            id = "selected";
        }

        return (
            <li class="ProofKitListItem" id={id} onClick={() => { change(index); }}>
                <img src={this.renderImage(proofKit.logo)} alt="Logo" />
                <h1>{proofKit.name}</h1>
                <span>{proofKit.description}</span>
            </li>
        );
    }
}

export default ProofKitListItem;