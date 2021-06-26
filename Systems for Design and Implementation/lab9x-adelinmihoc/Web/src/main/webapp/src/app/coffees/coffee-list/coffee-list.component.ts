import { Component, OnInit } from '@angular/core';
import {Coffee} from "../shared/coffee.model";
import {CoffeeService} from "../shared/coffee.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-coffee-list',
  templateUrl: './coffee-list.component.html',
  styleUrls: ['./coffee-list.component.css']
})
export class CoffeeListComponent implements OnInit {
  coffees!: Coffee[];

  constructor(private coffeeService: CoffeeService, private router: Router) { }

  ngOnInit(): void {
    this.coffeeService.getCoffees()
      .subscribe(coffees => this.coffees = coffees);
  }

  deleteCoffee(id: number) {
    this.coffeeService.deleteCoffee(id).subscribe(v => console.log(v));
    window.location.reload();
  }

  goToUpdate(cid: number, cname: string, corigin: string, cprice: number, cquantity: number) {
    this.router.navigateByUrl('/coffee-update', {state: {cid, cname, corigin, cprice, cquantity}});
  }
}
