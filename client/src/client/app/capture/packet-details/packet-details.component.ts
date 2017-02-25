import { Component, OnInit, ElementRef, NgZone } from '@angular/core';
import * as d3 from 'd3';

import { PacketService, Packet } from './../../shared/packet/index';

declare var $: any;

@Component({
  moduleId: module.id,
  selector: 'packet-details',
  templateUrl: 'packet-details.component.html'
})
export class PacketDetailsComponent {

  public packetToDisplay: Packet = null;

  private readonly heightDecreaseCoefficient: number = 3;
  private width: number = window.innerWidth;
  private height: number = window.innerHeight / this.heightDecreaseCoefficient;

  private xScale: d3.scale.Linear<number, number>;
  private yScale: d3.scale.Linear<number, number>;

  private group: d3.selection.Update<any>;

  private xCoefficient: number;
  private yCoefficient: number;

  constructor(
    private packetService: PacketService,
    private element: ElementRef,
    private ngZone: NgZone) {
      packetService.observedPacket.subscribe((packet: Packet) => {
        if (Object.keys(packet).length > 0) {
          if (this.packetToDisplay) {
            $('.chart').remove();
          }

          this.packetToDisplay = packet;
          this.displayPacket();
        }
      });

      window.onresize = (e) => {
        ngZone.run(() => {
          this.width = window.innerWidth;
          this.height = window.innerHeight / this.heightDecreaseCoefficient;

          if (this.packetToDisplay) {
            $('.chart').remove();
          }

          this.displayPacket();
        });
      };
  }

  private displayPacket() {
    this.xScale = d3.scale.linear().range([0, this.width]);
    this.yScale = d3.scale.linear().range([0, this.height]);

    let visualSelection: d3.Selection<any> =
      d3.select(this.element.nativeElement)
        .append('div')
        .attr('class', 'chart')
        .style('width', this.width + 'px')
        .style('height', this.height + 'px')
        .append('svg:svg')
        .attr('width', this.width)
        .attr('height', this.height);

    let partition: d3.layout.Partition<d3.layout.partition.Node> =
      d3.layout.partition().value((node: any) => node.size);

    this.group = <d3.selection.Update<any>>visualSelection.selectAll('g')
      .data(partition.nodes(this.packetToDisplay.data))
      .enter()
      .append('svg:g')
      .attr('transform', (node: d3.layout.partition.Node) =>
          'translate(' + this.xScale(node.y) + ',' + this.yScale(node.x) + ')')
      .on('click', this.nodeClicked.bind(this));

    this.xCoefficient = this.width / this.packetToDisplay.data.dx;
    this.yCoefficient = this.height / 1;

    this.group.append('svg:rect')
      .attr('width', this.packetToDisplay.data.dy * this.xCoefficient)
      .attr('height', (node: d3.layout.partition.Node) =>
            node.dx * this.yCoefficient)
      .attr('class', (node: d3.layout.partition.Node) =>
            node.children ? 'parent': 'child');

    this.group.append('svg:text')
      .attr('transform', this.transform.bind(this))
      .attr('dy', '.35em')
      .style('opacity', (node: d3.layout.partition.Node) =>
             node.dx * this.yCoefficient > 12 ? 1 : 0)
      .text((node: any) => node.name);

    d3.select(window)
      .on('click', () => this.nodeClicked(this.packetToDisplay.data));
  }

  private nodeClicked(node: d3.layout.partition.Node) {
    if (!node.children) {
      return;
    }

    this.xCoefficient = (node.y ? this.width - 40 : this.width) / (1 - node.y);
    this.yCoefficient = this.height / node.dx;

    this.xScale.domain([node.y, 1]).range([node.y ? 40 : 0, this.width]);
    this.yScale.domain([node.x, node.x + node.dx]);

    let transition = this.group.transition()
      .duration(750)
      .attr('transform', (node: d3.layout.partition.Node) => 'translate(' +
            this.xScale(node.y) + ',' + this.yScale(node.x) + ')');

    transition.select('rect')
      .attr('width', node.dy * this.xCoefficient)
      .attr('height', (node: d3.layout.partition.Node) =>
            node.dx * this.yCoefficient);

    transition.select('text')
      .attr('transform', this.transform.bind(this))
      .style('opacity', (node: d3.layout.partition.Node) =>
             node.dx * this.yCoefficient > 12 ? 1 : 0);

    (d3.event as Event).stopPropagation();
  }

  private transform(node: d3.layout.partition.Node) {
    return 'translate(8,' + node.dx * this.yCoefficient / 2 + ')';
  }
}
