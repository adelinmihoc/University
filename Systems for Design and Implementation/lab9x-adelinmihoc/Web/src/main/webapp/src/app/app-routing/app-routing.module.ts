import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import {RouterModule, Routes} from "@angular/router";
import {AddressesComponent} from "../addresses/addresses.component";
import {CoffeesComponent} from "../coffees/coffees.component";
import {CustomersComponent} from "../customers/customers.component";
import {OrdersComponent} from "../orders/orders.component";
import {OrderAddComponent} from "../orders/order-add/order-add.component";
import {AddressAddComponent} from "../addresses/address-add/address-add.component";
import {AddressDeleteComponent} from "../addresses/address-delete/address-delete.component";
import {AddressUpdateComponent} from "../addresses/address-update/address-update.component";
import {CoffeeAddComponent} from "../coffees/coffee-add/coffee-add.component";
import {CoffeeDeleteComponent} from "../coffees/coffee-delete/coffee-delete.component";
import {CoffeeUpdateComponent} from "../coffees/coffee-update/coffee-update.component";
import {CoffeeFilterComponent} from "../coffees/coffee-filter/coffee-filter.component";
import {CustomerAddComponent} from "../customers/customer-add/customer-add.component";
import {CustomerDeleteComponent} from "../customers/customer-delete/customer-delete.component";
import {CustomerUpdateComponent} from "../customers/customer-update/customer-update.component";
import {CustomerFilterComponent} from "../customers/customer-filter/customer-filter.component";
import {OrderDeleteComponent} from "../orders/order-delete/order-delete.component";
import {OrderUpdateComponent} from "../orders/order-update/order-update.component";
import {OrderFilterComponent} from "../orders/order-filter/order-filter.component";

const routes: Routes = [
  {path: 'addresses', component: AddressesComponent},
  {path: 'coffees', component: CoffeesComponent},
  {path: 'customers', component: CustomersComponent},
  {path: 'orders', component: OrdersComponent},

  {path: 'address-add', component: AddressAddComponent},
  {path: 'address-delete', component: AddressDeleteComponent},
  {path: 'address-update', component: AddressUpdateComponent},

  {path: 'coffee-add', component: CoffeeAddComponent},
  {path: 'coffee-delete', component: CoffeeDeleteComponent},
  {path: 'coffee-update', component: CoffeeUpdateComponent},
  {path: 'coffee-filter', component: CoffeeFilterComponent},

  {path: 'customer-add', component: CustomerAddComponent},
  {path: 'customer-delete', component: CustomerDeleteComponent},
  {path: 'customer-update', component: CustomerUpdateComponent},
  {path: 'customer-filter', component: CustomerFilterComponent},

  {path: 'order-add', component: OrderAddComponent},
  {path: 'order-delete', component: OrderDeleteComponent},
  {path: 'order-update', component: OrderUpdateComponent},
  {path: 'order-filter', component: OrderFilterComponent},
]

@NgModule({
  declarations: [],
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
