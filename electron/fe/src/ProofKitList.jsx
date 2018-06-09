import React, { Component } from 'react';
import ProofKitListItem from './ProofKitListItem';

class ProofKitList extends Component{
    render() {
        const { items, selected, change } = this.props;
        return (
            <ul class="ProofKitList">
            {items.map((proofKit, index) => {
                if(index === selected) {
                    return <ProofKitListItem index={index} selected={true} proofKit={proofKit} change={change}/>;
                } else {
                    return <ProofKitListItem index={index} selected={false} proofKit={proofKit} change={change}/>;
                }
            })}
            </ul>
        );
    }
}

export default ProofKitList;