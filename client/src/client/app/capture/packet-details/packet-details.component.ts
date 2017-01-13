import { Component, OnInit, ElementRef } from '@angular/core';
import * as d3 from 'd3';

/**
 * This class represents the lazy loaded PacketDetailsComponent.
 */
@Component({
  moduleId: module.id,
  selector: 'packet-details',
  templateUrl: 'packet-details.component.html',
  styleUrls: ['packet-details.component.css'],
})
export class PacketDetailsComponent {
  private width: Number = 1120;
  private height: Number = 300;

  private xScale = d3.scale.linear().range([0, this.width]);
  private yScale = d3.scale.linear().range([0, this.height]);

  private xCoefficient;
  private yCoefficient;

  constructor(private element: ElementRef) {
    let inputObject = {
  "children": [
    {
      "children": [
        {
          "children": null,
          "name": "9c:2a:70:1b:50:bd",
          "size": 6
        }
      ],
      "name": "destination_address"
    },
    {
      "children": [
        {
          "children": null,
          "name": "b8:62:1f:51:f4:1b",
          "size": 6
        }
      ],
      "name": "source_address"
    },
    {
      "children": [
        {
          "children": null,
          "name": 2048,
          "size": 2
        }
      ],
      "name": "ether_type"
    },
    {
      "children": [
        {
          "children": [
            {
              "children": null,
              "name": "192.168.1.101",
              "size": 4
            }
          ],
          "name": "destination_address"
        },
        {
          "children": [
            {
              "children": null,
              "name": "192.30.253.125",
              "size": 4
            }
          ],
          "name": "source_address"
        },
        {
          "children": [
            {
              "children": null,
              "name": 4,
              "size": 1
            }
          ],
          "name": "version"
        },
        {
          "children": [
            {
              "children": null,
              "name": 6,
              "size": 1
            }
          ],
          "name": "upper_layer"
        },
        {
          "children": [
            {
              "children": null,
              "name": 12,
              "size": 1
            }
          ],
          "name": "length"
        },
        {
          "children": [
            {
              "children": [
                {
                  "name": 64893,
                  "size": 2
                }
              ],
              "name": "destination_port"
            },
            {
              "children": [
                {
                  "name": 49182,
                  "size": 2
                }
              ],
              "name": "source_port"
            },
            {
              "children": [
                {
                  "name": 16,
                  "size": 1
                }
              ],
              "name": "length"
            }
          ],
          "name": "tcp"
        }
      ],
      "name": "internet"
    }
  ],
  "name": "ethernet"
};

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
      .data(partition.nodes(inputObject))
      .enter()
      .append('svg:g')
      .attr('transform',
            node => 'translate(' + this.xScale(node.y) + ',' +
              this.yScale(node.x) + ')')
      .on('click', this.nodeClicked.bind(this));

    // In Cartesian orientation, x, y, dx and dy correspond to the "x", "y",
    // "width" and "height" attributes of the SVG rect element.

    this.xCoefficient = this.width / inputObject.dx;
    this.yCoefficient = this.height / 1;

    this.group.append('svg:rect')
      .attr('width', inputObject.dy * this.xCoefficient)
      .attr('height', node => node.dx * this.yCoefficient)
      .attr('class', node => node.children ? 'parent': 'child');

    this.group.append('svg:text')
      .attr('transform', this.transform.bind(this))
      .attr('dy', '.35em')
      .style('opacity', node => node.dx * this.yCoefficient > 12 ? 1 : 0)
      .text(node => node.name)

    d3.select(window).on('click', () => this.nodeClicked(root));
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
