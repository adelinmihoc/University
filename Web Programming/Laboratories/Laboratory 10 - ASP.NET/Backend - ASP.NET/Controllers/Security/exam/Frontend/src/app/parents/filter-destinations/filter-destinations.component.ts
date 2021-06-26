import { Component, OnInit } from '@angular/core';
import {ParentService} from "../shared/parent.service";
import {Parent} from "../shared/parent.model";


@Component({
  selector: 'app-filter-destinations',
  templateUrl: './filter-destinations.component.html',
  styleUrls: ['./filter-destinations.component.css']
})
export class FilterDestinationsComponent implements OnInit {
  destinations!: Parent[];
  map = new Map<string, number>();
  reportStatus: any;

  constructor(private destinationService: ParentService) {
  }

  ngOnInit(): void {
  }

  filter(name: string) {
    this.destinations = [];
    this.destinationService.filterByName(name)
      .subscribe(destinations => {
        this.destinations = destinations;
        this.report();
      });
  }

  report() {
    for (let dest of this.destinations) {
      let value = this.map.get(JSON.stringify(dest));
      if (value === undefined) {
        value = 0;
      }
      this.map.set(JSON.stringify(dest), value + 1);
    }
  }

  doReport() {
    var mapAsc = new Map([...this.map].sort((a, b) =>
      String(b[1]).localeCompare(String(a[1]))
    ));

    this.reportStatus = [
      JSON.parse([...mapAsc][0][0]),
      JSON.parse([...mapAsc][1][0]),
      JSON.parse([...mapAsc][2][0])
    ];
  }
}

