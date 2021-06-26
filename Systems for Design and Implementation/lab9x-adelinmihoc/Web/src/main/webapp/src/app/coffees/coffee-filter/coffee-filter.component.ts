import { Component, OnInit } from '@angular/core';
import {Coffee} from "../shared/coffee.model";
import {CoffeeService} from "../shared/coffee.service";

@Component({
  selector: 'app-coffee-filter',
  templateUrl: './coffee-filter.component.html',
  styleUrls: ['./coffee-filter.component.css']
})
export class CoffeeFilterComponent implements OnInit {
  coffees!: Coffee[];
  searchtext!: string;

  constructor(private coffeeService: CoffeeService) { }

  ngOnInit(): void {
    this.coffeeService.getCoffees()
      .subscribe(coffees => this.coffees = coffees);
  }

  // filterCoffeesByName(name: string) {
  //   this.coffeeService.filterCoffeeByName(name)
  //     .subscribe(coffees => this.coffees = coffees);
  // }

  filterCoffeesByOrigin(origin: string) {
    this.coffeeService.filterCoffeeByOrigin(origin)
      .subscribe(coffees => this.coffees = coffees);
  }

}
