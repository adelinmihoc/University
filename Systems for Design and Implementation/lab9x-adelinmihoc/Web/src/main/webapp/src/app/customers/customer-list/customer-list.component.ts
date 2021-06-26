import { Component, OnInit } from '@angular/core';
import {Customer} from "../shared/customer.model";
import {CustomerService} from "../shared/customer.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-customer-list',
  templateUrl: './customer-list.component.html',
  styleUrls: ['./customer-list.component.css']
})
export class CustomerListComponent implements OnInit {
  customers!: Customer[];

  constructor(private customerService: CustomerService, private router: Router) { }

  ngOnInit(): void {
    this.customerService.getCustomers()
      .subscribe(customers => this.customers = customers);
  }

  deleteCustomer(id: number) {
    this.customerService.deleteCustomer(id);
    window.location.reload();
  }

  goToUpdate(cid: number, cfirstname: string, clastname: string,
             cphonenumber: string, cage: number, caddressid: number) {
    this.router.navigateByUrl('/customer-update', {state: {cid, cfirstname,
        clastname, cphonenumber, cage, caddressid}});
  }
}
