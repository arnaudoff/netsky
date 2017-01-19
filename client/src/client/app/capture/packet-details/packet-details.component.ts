import { Component, OnInit, ElementRef } from '@angular/core';
import * as d3 from 'd3';

import { PacketService, Packet } from './../../shared/packet/index';

@Component({
  moduleId: module.id,
  selector: 'packet-details',
  templateUrl: 'packet-details.component.html',
  styleUrls: ['packet-details.component.css'],
})
export class PacketDetailsComponent {

  private readonly width: Number = 1120;
  private readonly height: Number = 300;

  private xScale = d3.scale.linear().range([0, this.width]);
  private yScale = d3.scale.linear().range([0, this.height]);

  private xCoefficient;
  private yCoefficient;

  private group: any;

  constructor(private packetService: PacketService, private element: ElementRef) {
    packetService.observedPacket.subscribe((packet: Packet) => {
      if (Object.keys(packet).length === 0) {
        console.log('Please select a packet from the list to visualise.');
      } else {
        this.drawHierarchy(packet);
      }
    });
  }

  private drawHierarchy(packet: Packet) {
    if (this.group != null) {
      this.group.exit().remove();
    }

    let visualSelection = d3.select(this.element.nativeElement)
      .append('div')
      .attr('class', 'chart')
      .style('width', this.width + 'px')
      .style('height', this.height + 'px')
      .append('svg:svg')
      .attr('width', this.width)
      .attr('height', this.height)

    let partition = d3.layout.partition()
      .value(node => node.size)

    this.group = visualSelection.selectAll('g')
      .data(partition.nodes(packet.data));

    this.group
      .append('svg:g')
      .attr('transform',
            node => 'translate(' + this.xScale(node.y) + ',' +
              this.yScale(node.x) + ')')
      .on('click', this.nodeClicked.bind(this));

    this.xCoefficient = this.width / packet.data.dx;
    this.yCoefficient = this.height / 1;

    this.group.append('svg:rect')
      .attr('width', packet.data.dy * this.xCoefficient)
      .attr('height', node => node.dx * this.yCoefficient)
      .attr('class', node => node.children ? 'parent': 'child');

    this.group.append('svg:text')
      .attr('transform', this.transform.bind(this))
      .attr('dy', '.35em')
      .style('opacity', node => node.dx * this.yCoefficient > 12 ? 1 : 0)
      .text(node => node.name)

    d3.select(window).on('click', () => this.nodeClicked(packet.data));
  }

  private nodeClicked(node: Object) {
    if (!node.children) {
      return;
    }

    this.xCoefficient = (node.y ? this.width - 40 : this.width) / (1 - node.y);
    this.yCoefficient = this.height / node.dx;

    this.xScale.domain([node.y, 1]).range([node.y ? 40 : 0, this.width]);
    this.yScale.domain([node.x, node.x + node.dx]);

    let transition = this.group.transition()
      .duration(d3.event.altKey ? 7500 : 750)
      .attr('transform', node => 'translate(' + this.xScale(node.y) + ',' +
            this.yScale(node.x) + ')');

    transition.select('rect')
      .attr('width', node.dy * this.xCoefficient)
      .attr('height', node => node.dx * this.yCoefficient);

    transition.select('text')
      .attr('transform', this.transform.bind(this))
      .style('opacity', node => node.dx * this.yCoefficient > 12 ? 1 : 0);

    d3.event.stopPropagation();
  }

  private transform(node: Object) {
    return 'translate(8,' + node.dx * this.yCoefficient / 2 + ')';
  }
}
